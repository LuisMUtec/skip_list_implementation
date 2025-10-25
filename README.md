# Skip List Implementation in C++

Una implementación completa de **Skip List** (Lista de Saltos) en C++.

## ¿Qué es una Skip List?

Una Skip List es una estructura de datos probabilística que permite búsquedas, inserciones y eliminaciones eficientes en tiempo **O(log n)** en promedio. Es una alternativa más simple a los árboles balanceados.

## Características

- **Template genérico**: Funciona con cualquier tipo de clave y valor
- **Operaciones eficientes**: O(log n) en promedio para búsqueda, inserción y eliminación
- **Probabilístico**: Usa aleatorización para determinar los niveles de los nodos
- **Fácil de entender**: Más simple que árboles AVL o Red-Black

## Estructura del Proyecto

```
skip_list_implementation/
├── SkipList.h      # Implementación de la clase SkipList
├── main.cpp        # Programa de demostración
└── README.md       # Este archivo
```

## Compilación

### Windows (MinGW/g++)
```bash
g++ -o skiplist main.cpp -std=c++11
./skiplist
```

### Windows (MSVC)
```bash
cl /EHsc main.cpp /std:c++14
./main.exe
```

### Linux/Mac
```bash
g++ -o skiplist main.cpp -std=c++11
./skiplist
```

## Uso

```cpp
#include "SkipList.h"

// Crear una Skip List
SkipList<int, string> skipList;

// Insertar elementos
skipList.insert(5, "cinco");
skipList.insert(10, "diez");

// Buscar elementos
string value;
if (skipList.search(5, value)) {
    cout << "Encontrado: " << value << endl;
}

// Eliminar elementos
skipList.remove(5);

// Verificar tamaño
cout << "Tamaño: " << skipList.size() << endl;

// Mostrar estructura
skipList.display();
```

## API Principal

### Constructor
```cpp
SkipList(int maxLevel = 16, float probability = 0.5)
```
- `maxLevel`: Nivel máximo permitido
- `probability`: Probabilidad de promoción a niveles superiores (típicamente 0.5)

### Métodos Públicos

| Método | Complejidad | Descripción |
|--------|-------------|-------------|
| `insert(K key, V value)` | O(log n) | Inserta o actualiza un par clave-valor |
| `search(K key, V& value)` | O(log n) | Busca una clave y retorna su valor |
| `remove(K key)` | O(log n) | Elimina un elemento por clave |
| `size()` | O(1) | Retorna el número de elementos |
| `empty()` | O(1) | Verifica si la lista está vacía |
| `clear()` | O(n) | Elimina todos los elementos |
| `display()` | O(n) | Muestra la estructura (debug) |

## Complejidad Temporal

| Operación | Promedio | Peor Caso |
|-----------|----------|-----------|
| Búsqueda  | O(log n) | O(n) |
| Inserción | O(log n) | O(n) |
| Eliminación | O(log n) | O(n) |
| Espacio   | O(n) | O(n log n) |

## Ventajas vs Árboles Balanceados

✅ Más simple de implementar
✅ No requiere rotaciones complejas
✅ Excelente rendimiento en operaciones concurrentes
✅ Código más fácil de entender y mantener

## Ejemplo de Salida

```
***** Skip List *****
Level 3: [9:Nueve] [21:Veintiuno]
Level 2: [7:Siete] [9:Nueve] [21:Veintiuno]
Level 1: [3:Tres] [7:Siete] [9:Nueve] [17:Diecisiete] [21:Veintiuno]
Level 0: [3:Tres] [6:Seis] [7:Siete] [9:Nueve] [12:Doce] [17:Diecisiete] [19:Diecinueve] [21:Veintiuno] [25:Veinticinco] [26:Veintiseis]
*********************
```

## Autor

Luis Fernando

## Licencia

MIT License
