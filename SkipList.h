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

/**
 * @brief Una implementación robusta y eficiente de Skip List
 * 
 * @tparam K Tipo de la clave (debe ser comparable con operator<)
 * @tparam V Tipo del valor
 * 
 * Características:
 * - Comparación simple con operator<
 * - Regla de los 5 (copy, move, destructor)
 * - Iteradores forward
 * - Exception safety
 * - Const-correctness
 * - Validación de parámetros
 */
template <typename K, typename V>
class SkipList {
private:
    // Verificar en tiempo de compilación que K es comparable
    static_assert(is_copy_constructible<K>::value, "Key type must be copy constructible");
    static_assert(is_copy_constructible<V>::value, "Value type must be copy constructible");
    
    // Nodo de la Skip List
    struct Node {
        K key;
        V value;
        vector<Node*> forward;
        
        Node(const K& k, const V& v, int level) 
            : key(k), value(v), forward(level + 1, nullptr) {}
        
        Node(K&& k, V&& v, int level) 
            : key(move(k)), value(move(v)), forward(level + 1, nullptr) {}
    };
    
    Node* header_;                      // Nodo cabecera
    int maxPossibleLevel_;              // Nivel máximo posible
    float probability_;                 // Probabilidad de promoción
    int maxLevel_;                      // Nivel máximo actual
    size_t size_;                       // Número de elementos
    
    mutable mt19937 rng_;
    mutable uniform_real_distribution<float> dist_;
    
    /*
     Decide si se incrementa el nivel del nuevo nodo o se para de aumentar.
    */
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
    
    /*
     Modifica el Skip list actual para ser una copia
     */
    void copyFrom(const SkipList& other) {
    
        maxPossibleLevel_ = other.maxPossibleLevel_;
        probability_ = other.probability_;
        maxLevel_ = 0;
        size_ = 0;
        
        
        header_ = new Node(K(), V(), maxPossibleLevel_);
        
    
        Node* current = other.header_->forward[0];
        while (current != nullptr) {
            insert(current->key, current->value); //Modificar insert en el aumento de tamano
            current = current->forward[0];
        }
    }
    
public:
    // ITERADOR 
    
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
    

    // CONSTRUCTORES   
    explicit SkipList(int maxLevel = 0,  //Cuando se crea se inicia con nivel 0 
                            float probability = 0.5f)
        : maxPossibleLevel_(maxLevel)
        , probability_(probability)
        , maxLevel_(0)
        , size_(0)
        , rng_(random_device{}())
        , dist_(0.0f, 1.0f) {
        
        if (probability <= 0.0f || probability >= 1.0f) {
            throw invalid_argument("probability debe estar entre 0 y 1 (exclusivo)");
        }
        
        // Crear nodo header
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
        
        // Dejar other en estado válido
        other.header_ = new Node(K(), V(), other.maxPossibleLevel_);
        other.maxLevel_ = 0;
        other.size_ = 0;
    }
    
    /**
     * @brief Operador de asignación por movimiento
     */
    SkipList& operator=(SkipList&& other) noexcept {
        if (this != &other) {
            // Limpiar datos actuales
            clear();
            delete header_;
            
            // Mover del otro
            header_ = other.header_;
            maxLevel_ = other.maxLevel_;
            maxPossibleLevel_ = other.maxPossibleLevel_;
            probability_ = other.probability_;
            size_ = other.size_;
            rng_ = move(other.rng_);
            dist_ = move(other.dist_);
            
            // Dejar other en estado válido
            other.header_ = new Node(K(), V(), other.maxPossibleLevel_);
            other.maxLevel_ = 0;
            other.size_ = 0;
        }
        return *this;
    }
    
    // MÉTODOS DE INSERCIÓN
    
    /**
     * Inserta o actualiza un par clave-valor (copia)
     * key Clave a insertar
     * value Valor a insertar
     * true si se insertó, false si se actualizó
     */

    void nuevo_max_level(){
        this->maxPossibleLevel_ = ceil(log(this->size_) / log(1/this->probability_));
    }

    bool insert(const K& key, const V& value) {
        vector<Node*> update(maxPossibleLevel_ + 1, nullptr);
        Node* current = header_;
        
        // Buscar la posición de inserción
        for (int i = maxLevel_; i >= 0; i--) {
            while (current->forward[i] != nullptr && 
                current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        // Si la clave ya existe, actualizar el valor
        if (current != nullptr && (current->key == key)) {
            current->value = value;
            return false;  // Actualización
        }
        
        // Generar nivel aleatorio
        int newLevel = randomLevel(); //Puede ser mas grande que maxpossiblelevel?
        
        // Actualizar maxLevel si es necesario. Altura de Header actualizado
        if (newLevel > maxLevel_) {
            
            for (int i = maxLevel_ + 1; i <= newLevel; i++) {
                update[i] = header_;
                header_->forward.push_back(nullptr); 
            }
            
            maxLevel_ = newLevel;
        }
        
        // Crear nuevo nodo
        Node* newNode = new Node(key, value, newLevel);
        
        // Actualizar punteros
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        
        size_++;
        nuevo_max_level();
        return true;  // Inserción
    }
    
    
    
    /**
     * @brief Construye e inserta in-place (C++11 emplace)
     */
    template<typename... Args>
    bool emplace(const K& key, Args&&... args) {
        return insert(key, V(forward<Args>(args)...));
    }
    
    // ==================== MÉTODOS DE BÚSQUEDA ====================
    
    /**
     * @brief Busca un valor por clave
     * @param key Clave a buscar
     * @param value Referencia donde guardar el valor encontrado
     * @return true si se encontró, false en caso contrario
     */
    bool search(const K& key, V& value) const {
        Node* current = header_;
        
        for (int i = maxLevel_; i >= 0; i--) {
            while (current->forward[i] != nullptr && 
                   current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        
        current = current->forward[0];
        
        if (current != nullptr && !(current->key < key) && !(key < current->key)) {
            value = current->value;
            return true;
        }
        
        return false;
    }
    
    /**
     * @brief Verifica si una clave existe
     */
    bool contains(const K& key) const {
        V dummy;
        return search(key, dummy);
    }
    
    /**
     * @brief Busca un elemento con acceso tipo mapa (lanza excepción si no existe)
     * @throws std::out_of_range si la clave no existe
     */
    V& at(const K& key) {
        Node* current = header_;
        
        for (int i = maxLevel_; i >= 0; i--) {
            while (current->forward[i] != nullptr && 
                   current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        
        current = current->forward[0];
        
        if (current != nullptr && !(current->key < key) && !(key < current->key)) {
            return current->value;
        }
        
        throw out_of_range("Clave no encontrada en SkipList");
    }
    
    /**
     * @brief Versión const de at()
     */
    const V& at(const K& key) const {
        Node* current = header_;
        
        for (int i = maxLevel_; i >= 0; i--) {
            while (current->forward[i] != nullptr && 
                   current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        
        current = current->forward[0];
        
        if (current != nullptr && !(current->key < key) && !(key < current->key)) {
            return current->value;
        }
        
        throw out_of_range("Clave no encontrada en SkipList");
    }
    
    /**
     * @brief Operador de acceso tipo mapa (inserta si no existe)
     */
    V& operator[](const K& key) {
        Node* current = header_;
        vector<Node*> update(maxPossibleLevel_ + 1, nullptr);
        
        for (int i = maxLevel_; i >= 0; i--) {
            while (current->forward[i] != nullptr && 
                   current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        // Si existe, retornar referencia al valor
        if (current != nullptr && !(current->key < key) && !(key < current->key)) {
            return current->value;
        }
        
        // Si no existe, insertar con valor por defecto
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
    
    // ==================== MÉTODOS DE ELIMINACIÓN ====================
    
    /**
     * @brief Elimina un elemento por clave
     * @param key Clave a eliminar
     * @return true si se eliminó, false si no existía
     */
    bool remove(const K& key) {
        vector<Node*> update(maxPossibleLevel_ + 1, nullptr);
        Node* current = header_;
        
        for (int i = maxLevel_; i >= 0; i--) {
            while (current->forward[i] != nullptr && 
                   current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        if (current == nullptr || current->key < key || key < current->key) {
            return false;
        }
        
        // Actualizar punteros
        for (int i = 0; i <= maxLevel_; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        
        delete current;
        
        // Actualizar maxLevel
        while (maxLevel_ > 0 && header_->forward[maxLevel_] == nullptr) {
            maxLevel_--;
        }
        
        size_--;
        return true;
    }
    
    /**
     * @brief Alias de remove() para compatibilidad
     */
    bool erase(const K& key) {
        return remove(key);
    }
    
    /**
     * @brief Limpia toda la lista
     */
    void clear() {
        freeList();
        
        for (int i = 0; i <= maxPossibleLevel_; i++) {
            header_->forward[i] = nullptr;
        }
        
        maxLevel_ = 0;
        size_ = 0;
    }
    
    // ==================== MÉTODOS DE CONSULTA ====================
    
    /**
     * @brief Retorna el número de elementos
     */
    size_t size() const noexcept {
        return size_;
    }
    
    /**
     * @brief Verifica si la lista está vacía
     */
    bool empty() const noexcept {
        return size_ == 0;
    }
    
    /**
     * @brief Retorna el nivel máximo actual
     */
    int maxLevel() const noexcept {
        return maxLevel_;
    }
    
    // ==================== ITERADORES ====================
    
    Iterator begin() {
        return Iterator(header_->forward[0]);
    }
    
    Iterator end() {
        return Iterator(nullptr);
    }
    
    // ==================== UTILIDADES ====================
    
    /**
     * @brief Muestra la estructura de la skip list (debugging)
     */
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
    
    /**
     * @brief Intercambia el contenido con otra skip list
     */
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

// Función global swap para ADL (Argument Dependent Lookup)
template <typename K, typename V>
void swap(SkipList<K, V>& a, SkipList<K, V>& b) noexcept {
    a.swap(b);
}

#endif // SKIPLIST_H
