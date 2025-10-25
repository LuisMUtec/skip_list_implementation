#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

template <typename K, typename V>
class SkipList {
private:
    // Nodo de la Skip List
    struct Node {
        K key;
        V value;
        std::vector<Node*> forward;  // Punteros hacia adelante en cada nivel
        
        Node(K k, V v, int level) : key(k), value(v), forward(level + 1, nullptr) {}
    };
    
    Node* header;           // Nodo cabecera
    int maxLevel;           // Nivel máximo actual
    int maxPossibleLevel;   // Nivel máximo posible
    float probability;      // Probabilidad para determinar niveles (típicamente 0.5)
    int size_;              // Número de elementos
    
    // Genera un nivel aleatorio para un nuevo nodo
    int randomLevel() {
        int level = 0;
        while ((float)rand() / RAND_MAX < probability && level < maxPossibleLevel) {
            level++;
        }
        return level;
    }
    
public:
    // Constructor
    SkipList(int maxLvl = 16, float prob = 0.5) 
        : maxPossibleLevel(maxLvl), probability(prob), maxLevel(0), size_(0) {
        srand(time(nullptr));
        // Crear nodo cabecera con valores mínimos
        header = new Node(K(), V(), maxPossibleLevel);
    }
    
    // Destructor
    ~SkipList() {
        Node* current = header;
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }
    
    // Insertar un par clave-valor
    void insert(K key, V value) {
        std::vector<Node*> update(maxPossibleLevel + 1, nullptr);
        Node* current = header;
        
        // Buscar la posición de inserción
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        // Si la clave ya existe, actualizar el valor
        if (current != nullptr && current->key == key) {
            current->value = value;
            return;
        }
        
        // Generar nivel aleatorio para el nuevo nodo
        int newLevel = randomLevel();
        
        // Si el nuevo nivel es mayor que el nivel actual, actualizar
        if (newLevel > maxLevel) {
            for (int i = maxLevel + 1; i <= newLevel; i++) {
                update[i] = header;
            }
            maxLevel = newLevel;
        }
        
        // Crear nuevo nodo
        Node* newNode = new Node(key, value, newLevel);
        
        // Actualizar punteros
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        
        size_++;
    }
    
    // Buscar un valor por clave
    bool search(K key, V& value) {
        Node* current = header;
        
        // Comenzar desde el nivel más alto
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        
        current = current->forward[0];
        
        // Verificar si encontramos la clave
        if (current != nullptr && current->key == key) {
            value = current->value;
            return true;
        }
        
        return false;
    }
    
    // Eliminar un elemento por clave
    bool remove(K key) {
        std::vector<Node*> update(maxPossibleLevel + 1, nullptr);
        Node* current = header;
        
        // Buscar el nodo a eliminar
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        // Si no se encuentra la clave
        if (current == nullptr || current->key != key) {
            return false;
        }
        
        // Actualizar punteros
        for (int i = 0; i <= maxLevel; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        
        delete current;
        
        // Actualizar el nivel máximo si es necesario
        while (maxLevel > 0 && header->forward[maxLevel] == nullptr) {
            maxLevel--;
        }
        
        size_--;
        return true;
    }
    
    // Verificar si la lista está vacía
    bool empty() const {
        return size_ == 0;
    }
    
    // Obtener el tamaño
    int size() const {
        return size_;
    }
    
    // Mostrar la skip list (para debugging)
    void display() {
        std::cout << "\n***** Skip List *****\n";
        for (int i = maxLevel; i >= 0; i--) {
            Node* node = header->forward[i];
            std::cout << "Level " << i << ": ";
            while (node != nullptr) {
                std::cout << "[" << node->key << ":" << node->value << "] ";
                node = node->forward[i];
            }
            std::cout << std::endl;
        }
        std::cout << "*********************\n";
    }
    
    // Limpiar toda la lista
    void clear() {
        Node* current = header->forward[0];
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
        
        for (int i = 0; i <= maxPossibleLevel; i++) {
            header->forward[i] = nullptr;
        }
        
        maxLevel = 0;
        size_ = 0;
    }
};

#endif // SKIPLIST_H
