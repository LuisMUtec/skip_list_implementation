#include "SkipList.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Crear una Skip List de enteros a strings
    SkipList<int, string> skipList;
    
    cout << "=== Demostracion de Skip List ===" << endl;
    
    // Insertar elementos
    cout << "\n1. Insertando elementos..." << endl;
    skipList.insert(3, "Tres");
    skipList.insert(6, "Seis");
    skipList.insert(7, "Siete");
    skipList.insert(9, "Nueve");
    skipList.insert(12, "Doce");
    skipList.insert(19, "Diecinueve");
    skipList.insert(17, "Diecisiete");
    skipList.insert(26, "Veintiseis");
    skipList.insert(21, "Veintiuno");
    skipList.insert(25, "Veinticinco");
    
    cout << "Elementos insertados: " << skipList.size() << endl;
    
    // Mostrar la estructura
    skipList.display();
    
    // Buscar elementos
    cout << "\n2. Buscando elementos..." << endl;
    string value;
    
    if (skipList.search(19, value)) {
        cout << "Clave 19 encontrada: " << value << endl;
    } else {
        cout << "Clave 19 no encontrada" << endl;
    }
    
    if (skipList.search(15, value)) {
        cout << "Clave 15 encontrada: " << value << endl;
    } else {
        cout << "Clave 15 no encontrada" << endl;
    }
    
    // Actualizar un valor existente
    cout << "\n3. Actualizando clave 7..." << endl;
    skipList.insert(7, "Siete (actualizado)");
    if (skipList.search(7, value)) {
        cout << "Clave 7 ahora tiene valor: " << value << endl;
    }
    
    // Eliminar elementos
    cout << "\n4. Eliminando elementos..." << endl;
    if (skipList.remove(19)) {
        cout << "Clave 19 eliminada exitosamente" << endl;
    }
    
    if (skipList.remove(100)) {
        cout << "Clave 100 eliminada exitosamente" << endl;
    } else {
        cout << "Clave 100 no existe" << endl;
    }
    
    cout << "Elementos restantes: " << skipList.size() << endl;
    
    // Mostrar estructura después de eliminaciones
    skipList.display();
    
    // Ejemplo con diferentes tipos de datos
    cout << "\n=== Skip List de doubles ===" << endl;
    SkipList<double, int> skipList2;
    
    skipList2.insert(3.14, 314);
    skipList2.insert(2.71, 271);
    skipList2.insert(1.41, 141);
    skipList2.insert(9.81, 981);
    
    skipList2.display();
    
    int intValue;
    if (skipList2.search(2.71, intValue)) {
        cout << "Valor encontrado para 2.71: " << intValue << endl;
    }
    
    // Limpiar
    cout << "\n5. Limpiando la primera lista..." << endl;
    skipList.clear();
    cout << "Lista vacia: " << (skipList.empty() ? "Si" : "No") << endl;
    cout << "Tamano: " << skipList.size() << endl;
    
    return 0;
}
