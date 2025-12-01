#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <functional>
#include <type_traits>

using namespace std;

template <typename K, typename V>
class SkipList {
private:
    static_assert(is_copy_constructible<K>::value, "Key type must be copy constructible");
    static_assert(is_copy_constructible<V>::value, "Value type must be copy constructible");
    
    struct Node {
        K key;
        V value;
        vector<Node*> forward;
        
        Node(const K& k, const V& v, int level) 
            : key(k), value(v), forward(level + 1, nullptr) {}
        
        Node(K&& k, V&& v, int level) 
            : key(move(k)), value(move(v)), forward(level + 1, nullptr) {}
    };
    
    Node* header_;
    int maxPossibleLevel_;
    float probability_;
    int maxLevel_;
    size_t size_;
    
    mt19937 rng_;
    uniform_real_distribution<float> dist_;
    
    int randomLevel() {
        int level = 0;
        while (dist_(rng_) < probability_ && level < maxPossibleLevel_) {
            level++;
        }
        return level;
    }
    
    void freeList() {
        Node* current = header_->forward[0];
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }
    
    Node* findNode(const K& key, vector<Node*>* update = nullptr) const {
        Node* current = header_;
        
        if (update) {
            update->resize(maxPossibleLevel_ + 1);
            for (int i = maxLevel_; i >= 0; i--) {
                while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                    current = current->forward[i];
                }
                (*update)[i] = current;
            }
        } else {
            for (int i = maxLevel_; i >= 0; i--) {
                while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                    current = current->forward[i];
                }
            }
        }
        
        return current->forward[0];
    }
    
    void copyFrom(const SkipList& other) {
        maxPossibleLevel_ = other.maxPossibleLevel_;
        probability_ = other.probability_;
        maxLevel_ = other.maxLevel_;
        size_ = other.size_;
        
        header_ = new Node(K(), V(), maxPossibleLevel_);
        
        if (other.size_ == 0) return;
        
        vector<Node*> update(maxPossibleLevel_ + 1, header_);
        Node* otherCurrent = other.header_->forward[0];
        
        while (otherCurrent != nullptr) {
            int level = static_cast<int>(otherCurrent->forward.size()) - 1;
            Node* newNode = new Node(otherCurrent->key, otherCurrent->value, level);
            
            for (int i = 0; i <= level; i++) {
                update[i]->forward[i] = newNode;
                update[i] = newNode;
            }
            
            otherCurrent = otherCurrent->forward[0];
        }
    }
    
public:
    class Iterator {
    private:
        Node* node_;
        
    public:
        using iterator_category = forward_iterator_tag;
        using value_type = pair<K&, V&>;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type;
        
        explicit Iterator(Node* node) : node_(node) {}
        
        reference operator*() const {
            return {node_->key, node_->value};
        }
        
        Iterator& operator++() {
            if (node_) node_ = node_->forward[0];
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const Iterator& other) const {
            return node_ == other.node_;
        }
        
        bool operator!=(const Iterator& other) const {
            return node_ != other.node_;
        }
        
        const K& key() const { return node_->key; }
        V& value() { return node_->value; }
        const V& value() const { return node_->value; }
    };
    
    explicit SkipList(int maxLevel = 16, float probability = 0.5f)
        : maxPossibleLevel_(maxLevel)
        , probability_(probability)
        , maxLevel_(0)
        , size_(0)
        , rng_(random_device{}())
        , dist_(0.0f, 1.0f) {
        
        if (probability <= 0.0f || probability >= 1.0f) {
            throw invalid_argument("probability debe estar entre 0 y 1 (exclusivo)");
        }
        
        header_ = new Node(K(), V(), maxPossibleLevel_);
    }
    
    ~SkipList() {
        clear();
        delete header_;
    }
    
    SkipList(const SkipList& other) 
        : rng_(random_device{}())
        , dist_(0.0f, 1.0f) {
        copyFrom(other);
    }
    
    SkipList& operator=(const SkipList& other) {
        if (this != &other) {
            // Limpiar datos actuales
            clear();
            delete header_;
            
            copyFrom(other);
        }
        return *this;
    }
    
    SkipList(SkipList&& other) noexcept
        : header_(other.header_)
        , maxPossibleLevel_(other.maxPossibleLevel_)
        , probability_(other.probability_)
        , maxLevel_(other.maxLevel_)
        , size_(other.size_)
        , rng_(move(other.rng_))
        , dist_(move(other.dist_)) {
        
        other.header_ = new Node(K(), V(), other.maxPossibleLevel_);
        other.maxLevel_ = 0;
        other.size_ = 0;
    }
    
    SkipList& operator=(SkipList&& other) noexcept {
        if (this != &other) {
            clear();
            delete header_;
            
            header_ = other.header_;
            maxLevel_ = other.maxLevel_;
            maxPossibleLevel_ = other.maxPossibleLevel_;
            probability_ = other.probability_;
            size_ = other.size_;
            rng_ = move(other.rng_);
            dist_ = move(other.dist_);
            
            other.header_ = new Node(K(), V(), other.maxPossibleLevel_);
            other.maxLevel_ = 0;
            other.size_ = 0;
        }
        return *this;
    }
    
    bool insert(const K& key, const V& value) {
        vector<Node*> update;
        update.reserve(maxPossibleLevel_ + 1);
        
        Node* current = findNode(key, &update);
        
        if (current != nullptr && current->key == key) {
            current->value = value;
            return false;
        }
        
        int newLevel = randomLevel();
        
        if (newLevel > maxLevel_) {
            for (int i = maxLevel_ + 1; i <= newLevel; i++) {
                update[i] = header_;
            }
            maxLevel_ = newLevel;
        }
        
        Node* newNode = new Node(key, value, newLevel);
        
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        
        size_++;
        return true;
    }
    
    
    template<typename... Args>
    bool emplace(const K& key, Args&&... args) {
        return insert(key, V(forward<Args>(args)...));
    }
    
    bool search(const K& key, V& value) const {
        Node* node = findNode(key);
        
        if (node != nullptr && node->key == key) {
            value = node->value;
            return true;
        }
        
        return false;
    }
    
    bool contains(const K& key) const {
        Node* node = findNode(key);
        return node != nullptr && node->key == key;
    }
    
    Iterator find(const K& key) {
        Node* node = findNode(key);
        if (node != nullptr && node->key == key) {
            return Iterator(node);
        }
        return end();
    }
    
    V& at(const K& key) {
        Node* node = findNode(key);
        
        if (node != nullptr && node->key == key) {
            return node->value;
        }
        
        throw out_of_range("Clave no encontrada en SkipList");
    }
    
    const V& at(const K& key) const {
        Node* node = findNode(key);
        
        if (node != nullptr && node->key == key) {
            return node->value;
        }
        
        throw out_of_range("Clave no encontrada en SkipList");
    }
    
    V& operator[](const K& key) {
        vector<Node*> update;
        update.reserve(maxPossibleLevel_ + 1);
        
        Node* current = findNode(key, &update);
        
        if (current != nullptr && current->key == key) {
            return current->value;
        }
        
        int newLevel = randomLevel();
        
        if (newLevel > maxLevel_) {
            for (int i = maxLevel_ + 1; i <= newLevel; i++) {
                update[i] = header_;
            }
            maxLevel_ = newLevel;
        }
        
        Node* newNode = new Node(key, V(), newLevel);
        
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        
        size_++;
        return newNode->value;
    }
    
    bool remove(const K& key) {
        vector<Node*> update;
        update.reserve(maxPossibleLevel_ + 1);
        
        Node* current = findNode(key, &update);
        
        if (current == nullptr || current->key != key) {
            return false;
        }
        
        for (int i = 0; i <= maxLevel_; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        
        delete current;
        
        while (maxLevel_ > 0 && header_->forward[maxLevel_] == nullptr) {
            maxLevel_--;
        }
        
        size_--;
        return true;
    }
    
    bool erase(const K& key) {
        return remove(key);
    }
    
    void clear() {
        freeList();
        
        for (int i = 0; i <= maxPossibleLevel_; i++) {
            header_->forward[i] = nullptr;
        }
        
        maxLevel_ = 0;
        size_ = 0;
    }
    
    size_t size() const noexcept {
        return size_;
    }
    
    bool empty() const noexcept {
        return size_ == 0;
    }
    
    int maxLevel() const noexcept {
        return maxLevel_;
    }
    
    Iterator begin() {
        return Iterator(header_->forward[0]);
    }
    
    Iterator end() {
        return Iterator(nullptr);
    }
    
    void display() const {
        cout << "\n***** Skip List (size=" << size_ << ") *****\n";
        for (int i = maxLevel_; i >= 0; i--) {
            Node* node = header_->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << "[" << node->key << ":" << node->value << "] ";
                node = node->forward[i];
            }
            cout << endl;
        }
        cout << "*********************\n";
    }
    
    void swap(SkipList& other) noexcept {
        using std::swap;
        swap(header_, other.header_);
        swap(maxLevel_, other.maxLevel_);
        swap(maxPossibleLevel_, other.maxPossibleLevel_);
        swap(probability_, other.probability_);
        swap(size_, other.size_);
        swap(rng_, other.rng_);
        swap(dist_, other.dist_);
    }
};

template <typename K, typename V>
void swap(SkipList<K, V>& a, SkipList<K, V>& b) noexcept {
    a.swap(b);
}

#endif
