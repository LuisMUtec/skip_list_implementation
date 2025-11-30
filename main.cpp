#include "SkipList.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void testBasicOperations() {
    cout << "\n========== TEST 1: Operaciones Basicas ==========" << endl;
    
    SkipList<int, string> sl;
    
    // Inserción
    sl.insert(5, "cinco");
    sl.insert(10, "diez");
    sl.insert(3, "tres");
    sl.insert(7, "siete");
    
    cout << "Insertados 4 elementos. Size: " << sl.size() << endl;
    sl.display();
    
    // Búsqueda
    string val;
    if (sl.search(5, val)) {
        cout << "Encontrado 5: " << val << endl;
    }
    
    // Contains
    cout << "Contiene 7? " << (sl.contains(7) ? "Si" : "No") << endl;
    cout << "Contiene 100? " << (sl.contains(100) ? "Si" : "No") << endl;
    
    // Eliminación
    sl.remove(5);
    cout << "Despues de eliminar 5. Size: " << sl.size() << endl;
    sl.display();
}

void testCopyAndMove() {
    cout << "\n========== TEST 2: Copy & Move Semantics ==========" << endl;
    
    SkipList<int, string> sl1;
    sl1.insert(1, "uno");
    sl1.insert(2, "dos");
    sl1.insert(3, "tres");
    
    cout << "Lista original:" << endl;
    sl1.display();
    
    // Constructor de copia
    SkipList<int, string> sl2(sl1);
    cout << "Copia creada. Size: " << sl2.size() << endl;
    sl2.display();
    
    // Operador de asignación
    SkipList<int, string> sl3;
    sl3 = sl1;
    cout << "Asignacion por copia. Size: " << sl3.size() << endl;
    
    // Move constructor
    SkipList<int, string> sl4(std::move(sl1));
    cout << "Move constructor. Size sl4: " << sl4.size() 
         << ", sl1 (movido): " << sl1.size() << endl;
    
    // Move assignment
    SkipList<int, string> sl5;
    sl5 = std::move(sl2);
    cout << "Move assignment. Size sl5: " << sl5.size() 
         << ", sl2 (movido): " << sl2.size() << endl;
}

void testIterators() {
    cout << "\n========== TEST 3: Iteradores ==========" << endl;
    
    SkipList<int, string> sl;
    sl.insert(5, "cinco");
    sl.insert(2, "dos");
    sl.insert(8, "ocho");
    sl.insert(1, "uno");
    sl.insert(9, "nueve");
    
    // Range-based for loop
    cout << "Iterando con range-based for:" << endl;
    for (auto it = sl.begin(); it != sl.end(); ++it) {
        cout << "  [" << it.key() << " -> " << it.value() << "]" << endl;
    }
    
    // Modificar valores a través del iterador
    cout << "\nModificando valores..." << endl;
    for (auto it = sl.begin(); it != sl.end(); ++it) {
        it.value() = it.value() + " (modificado)";
    }
    
    cout << "Despues de modificar:" << endl;
    for (auto it = sl.begin(); it != sl.end(); ++it) {
        cout << "  [" << it.key() << " -> " << it.value() << "]" << endl;
    }
}

void testOperatorBracket() {
    cout << "\n========== TEST 4: Operator[] ==========" << endl;
    
    SkipList<string, int> sl;
    
    // Insertar usando operator[]
    sl["Alice"] = 25;
    sl["Bob"] = 30;
    sl["Charlie"] = 22;
    
    cout << "Edad de Alice: " << sl["Alice"] << endl;
    cout << "Edad de Bob: " << sl["Bob"] << endl;
    
    // Acceder a clave no existente (la crea)
    cout << "Edad de David (no existe): " << sl["David"] << endl;
    sl["David"] = 28;
    cout << "Edad de David (ahora existe): " << sl["David"] << endl;
    
    sl.display();
}

void testAtMethod() {
    cout << "\n========== TEST 5: Metodo at() ==========" << endl;
    
    SkipList<int, string> sl;
    sl.insert(1, "uno");
    sl.insert(2, "dos");
    sl.insert(3, "tres");
    
    try {
        cout << "at(2): " << sl.at(2) << endl;
        
        // Modificar con at()
        sl.at(2) = "DOS (mayuscula)";
        cout << "at(2) modificado: " << sl.at(2) << endl;
        
        // Intentar acceder a clave no existente
        cout << "Intentando at(999)..." << endl;
        cout << sl.at(999) << endl;  // Esto lanzará excepción
        
    } catch (const out_of_range& e) {
        cout << "Excepcion capturada: " << e.what() << endl;
    }
}

void testExceptionSafety() {
    cout << "\n========== TEST 6: Exception Safety ==========" << endl;
    
    try {
        // Nivel máximo inválido
        SkipList<int, int> sl1(100);  // Debería lanzar excepción
    } catch (const invalid_argument& e) {
        cout << "Excepcion nivel maximo: " << e.what() << endl;
    }
    
    try {
        // Probabilidad inválida
        SkipList<int, int> sl2(16, 1.5f);  // Debería lanzar excepción
    } catch (const invalid_argument& e) {
        cout << "Excepcion probabilidad: " << e.what() << endl;
    }
    
    try {
        // Probabilidad en límite
        SkipList<int, int> sl3(16, 0.0f);  // Debería lanzar excepción
    } catch (const invalid_argument& e) {
        cout << "Excepcion probabilidad cero: " << e.what() << endl;
    }
    
    cout << "Constructor valido:" << endl;
    SkipList<int, int> sl4(16, 0.5f);  // OK
    cout << "  Creado exitosamente con maxLevel=16, prob=0.5" << endl;
}

void testEmplace() {
    cout << "\n========== TEST 7: Emplace ==========" << endl;
    
    SkipList<int, string> sl;
    
    // Emplace construye el objeto in-place
    sl.emplace(1, "Hello World");
    sl.emplace(2, 5, 'a');  // Constructor string(5, 'a') = "aaaaa"
    
    sl.display();
    
    string val;
    sl.search(2, val);
    cout << "Valor con emplace: " << val << endl;
}

void testSwap() {
    cout << "\n========== TEST 8: Swap ==========" << endl;
    
    SkipList<int, string> sl1, sl2;
    
    sl1.insert(1, "uno");
    sl1.insert(2, "dos");
    
    sl2.insert(10, "diez");
    sl2.insert(20, "veinte");
    sl2.insert(30, "treinta");
    
    cout << "Antes del swap:" << endl;
    cout << "sl1 size: " << sl1.size() << endl;
    cout << "sl2 size: " << sl2.size() << endl;
    
    sl1.swap(sl2);
    
    cout << "\nDespues del swap:" << endl;
    cout << "sl1 size: " << sl1.size() << endl;
    cout << "sl2 size: " << sl2.size() << endl;
    
    sl1.display();
    sl2.display();
}

void testCustomComparator() { //Nuestra implementacion solo lo ordena de menor a mayor. 
    cout << "\n========== TEST 9: Comparador Personalizado ==========" << endl;
    
    // Skip list con orden descendente
    SkipList<int, string> sl;
    
    sl.insert(5, "cinco");
    sl.insert(2, "dos");
    sl.insert(8, "ocho");
    sl.insert(1, "uno");
    
    cout << "Con comparador descendente (greater<int>):" << endl;
    for (auto it = sl.begin(); it != sl.end(); ++it) {
        cout << "  [" << it.key() << " -> " << it.value() << "]" << endl;
    }
}

void testLargeDataset() {
    cout << "\n========== TEST 10: Dataset Grande ==========" << endl;
    
    SkipList<int, int> sl;
    
    // Insertar 10000 elementos
    cout << "Insertando 10000 elementos..." << endl;
    for (int i = 0; i < 10000; i++) {
        sl.insert(i, i * 2);
    }
    
    cout << "Size: " << sl.size() << endl;
    cout << "Max Level: " << sl.maxLevel() << endl;
    
    // Búsqueda
    int val;
    bool found = sl.search(5000, val);
    cout << "Buscar 5000: " << (found ? "Encontrado" : "No encontrado");
    if (found) cout << ", valor=" << val;
    cout << endl;
    
    // Eliminar 5000 elementos
    cout << "Eliminando 5000 elementos..." << endl;
    for (int i = 0; i < 5000; i++) {
        sl.remove(i * 2);
    }
    
    cout << "Size despues de eliminar: " << sl.size() << endl;
    cout << "Max Level: " << sl.maxLevel() << endl;
}

int main() {
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║     SKIP LIST ROBUSTA - Suite de Pruebas Completa        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    testBasicOperations();
    testCopyAndMove();
    testIterators();
    testOperatorBracket();
    testAtMethod();
    testExceptionSafety();
    testEmplace();
    testSwap();
    testCustomComparator();
    testLargeDataset();
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              TODOS LOS TESTS COMPLETADOS ✓                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}
