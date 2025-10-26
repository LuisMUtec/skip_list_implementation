# Skip List - Implementación en C++# Skip List - Implementación en C++# Skip List - Implementación en C++# Skip List



Implementación de Skip List en C++ siguiendo estándares modernos de C++11, basada en el trabajo original de William Pugh (1990).

## ¿Qué es?

## Definición



Skip List es una estructura de datos probabilística que proporciona operaciones de búsqueda, inserción y eliminación con complejidad temporal esperada O(log n). Constituye una alternativa a los árboles balanceados tradicionales (AVL, Red-Black).

Skip List es una estructura de datos probabilística que permite operaciones en **O(log n)** promedio. Alternativa simple a árboles balanceados.

## Propiedades

Una Skip List es una estructura de datos probabilística que permite búsquedas, inserciones y eliminaciones eficientes en tiempo **O(log n)** en promedio. Es una alternativa más simple a los árboles balanceados (AVL, Red-Black).

La estructura se caracteriza por:

**Ventajas:**

- Implementación simple que no requiere operaciones de rotación

- Balanceo automático mediante técnicas probabilísticas- ✅ Implementación simple (sin rotaciones)

- Rendimiento eficiente en entornos concurrentes

- Complejidad espacial O(n) en el caso promedio- ✅ Excelente para concurrencia



## Características de Implementación- ✅ Balanceo automático probabilístico### Ventajas sobre árboles balanceados:## ¿Qué es una Skip List?## ¿Qué es una Skip List?



Esta implementación incorpora las siguientes características técnicas:



- **Regla de los Cinco**: Implementación completa de constructores de copia/movimiento y operadores de asignación## Características- ✅ Más simple de implementar (no requiere rotaciones)

- **Generación Aleatoria Moderna**: Utilización de `std::mt19937` para generación de números pseudoaleatorios de alta calidad

- **Iteradores Conformes a STL**: Iteradores forward tanto mutables como constantes

- **Seguridad de Excepciones**: Validación exhaustiva de parámetros y garantías de seguridad de excepciones

- **Corrección de const**: Métodos const apropiados para garantizar inmutabilidad- **Regla de los 5**: Copy/Move semantics completos- ✅ Mejor rendimiento en operaciones concurrentes

- **Interfaz Compatible con STL**: Métodos similares a `std::map` incluyendo `operator[]`, `at()`, y `contains()`

- **std::mt19937**: Generador aleatorio moderno

## Compilación

- **Iteradores**: Forward iterators (const y mutable)- ✅ Código más fácil de entender y mantener

### Requisitos

- **Exception safety**: Validación completa

- Compilador compatible con C++11 o superior (g++, clang++, MSVC)

- **Interfaz STL**: `operator[]`, `at()`, `contains()`, etc.- ✅ Balanceo automático vía aleatorizaciónUna Skip List es una estructura de datos probabilística que permite búsquedas, inserciones y eliminaciones eficientes en tiempo **O(log n)** en promedio. Es una alternativa más simple a los árboles balanceados (AVL, Red-Black).Una Skip List es una estructura de datos probabilística que permite búsquedas, inserciones y eliminaciones eficientes en tiempo **O(log n)** en promedio. Es una alternativa más simple a los árboles balanceados (como el AVL).

### Instrucciones de Compilación



```bash

g++ -o skiplist main.cpp -std=c++11 -Wall -Wextra## Compilación

./skiplist

```



## Interfaz de Programación```bash## Características



### Ejemplo de Uso Básicog++ -o skiplist main.cpp -std=c++11



```cpp./skiplist

#include "SkipList.h"

```

SkipList<int, std::string> lista;

### Características Profesionales:### Ventajas sobre árboles balanceados:## Características

// Inserción

lista.insert(5, "cinco");## Uso Básico

lista[10] = "diez";

- **Regla de los 5**: Copy/Move constructors y assignment operators

// Búsqueda

std::string valor;```cpp

if (lista.search(5, valor)) {

    // Elemento encontrado#include "SkipList.h"- **Generador aleatorio moderno**: `std::mt19937` (thread-safe)- ✅ Más simple de implementar (no requiere rotaciones)

}



if (lista.contains(10)) {

    // Verificación de existenciaSkipList<int, std::string> sl;- **Iteradores completos**: Forward iterators (const y mutable)

}



// Eliminación

lista.remove(5);// Inserción- **Exception safety**: Validación de parámetros y manejo de errores- ✅ Mejor rendimiento en operaciones concurrentes- **Template genérico**: Funciona con cualquier tipo de clave y valor

```

sl.insert(5, "cinco");

### Métodos Principales

sl[10] = "diez";           // Estilo map- **Const-correctness**: Métodos const apropiados

| Método | Complejidad Temporal | Descripción |

|--------|---------------------|-------------|

| `insert(key, value)` | O(log n) | Inserta o actualiza un par clave-valor |

| `search(key, value)` | O(log n) | Busca un valor asociado a una clave |// Búsqueda- **Type traits**: Validación en tiempo de compilación- ✅ Código más fácil de entender y mantener- **Operaciones eficientes**: O(log n) en promedio para búsqueda, inserción y eliminación

| `contains(key)` | O(log n) | Verifica la existencia de una clave |

| `at(key)` | O(log n) | Acceso con verificación de límites |std::string val;

| `operator[](key)` | O(log n) | Acceso o inserción estilo asociativo |

| `remove(key)` | O(log n) | Elimina un elemento |if (sl.search(5, val)) { }- **Compilación limpia**: Sin warnings con `-Wall -Wextra`

| `size()` | O(1) | Retorna el número de elementos |

| `clear()` | O(n) | Elimina todos los elementos |if (sl.contains(10)) { }



### Características Avanzadas- ✅ Balanceo automático via aleatorización- **Probabilístico**: Usa aleatorización para determinar los niveles de los nodos



#### Iteradores// Eliminación



```cppsl.remove(5);### API Completa:

for (auto it = lista.begin(); it != lista.end(); ++it) {

    std::cout << it.key() << " : " << it.value() << "\n";```

}

```- `insert()` / `emplace()` - Inserción eficiente- : Más simple que árboles AVL o Red-Black



#### Semántica de Copia y Movimiento## API Principal



```cpp- `search()` / `contains()` - Búsqueda

SkipList<int, int> lista1;

SkipList<int, int> lista2(lista1);           // Copia profunda| Método | Complejidad | Descripción |

SkipList<int, int> lista3(std::move(lista1)); // Transferencia de propiedad

```|--------|-------------|-------------|- `at()` / `operator[]` - Acceso tipo `std::map`



#### Comparador Personalizado| `insert(key, value)` | O(log n) | Inserta o actualiza |



```cpp| `search(key, value)` | O(log n) | Busca valor |- `remove()` / `erase()` - Eliminación

SkipList<int, std::string, std::greater<int>> listaDesc;

```| `contains(key)` | O(log n) | Verifica existencia |



#### Construcción In-Place| `at(key)` | O(log n) | Acceso seguro (excepción) |- `begin()` / `end()` - Iteradores## Estructura del Proyecto



```cpp| `operator[](key)` | O(log n) | Acceso/inserción |

lista.emplace(1, 5, 'X'); // Construye el valor directamente en la estructura

```| `remove(key)` | O(log n) | Elimina elemento |- `size()` / `empty()` / `clear()` - Utilidades



## Análisis de Complejidad| `size()` | O(1) | Número de elementos |



### Complejidad Temporal| `clear()` | O(n) | Vacía la lista |- `swap()` - Intercambio eficiente### Características Profesionales:



| Operación | Caso Promedio | Peor Caso |

|-----------|---------------|-----------|

| Búsqueda | O(log n) | O(n) |## Características Avanzadas- `display()` - Visualización para debugging

| Inserción | O(log n) | O(n) |

| Eliminación | O(log n) | O(n) |



### Complejidad Espacial```cpp- **Regla de los 5**: Copy/Move constructors y assignment operators```



| Métrica | Caso Promedio | Peor Caso |// Iteradores

|---------|---------------|-----------|

| Espacio | O(n) | O(n log n) |for (auto it = sl.begin(); it != sl.end(); ++it) {## 📁 Estructura del Proyecto



## Validación    std::cout << it.key() << " : " << it.value() << "\n";



El archivo `main.cpp` contiene una suite de pruebas exhaustiva que verifica:}- **Generador aleatorio moderno**: `std::mt19937` (thread-safe)skip_list_implementation/



1. Operaciones básicas de inserción, búsqueda y eliminación

2. Semántica de copia y movimiento

3. Funcionamiento de iteradores// Copy/Move```

4. Operadores de acceso estilo mapa

5. Manejo de excepcionesSkipList<int, int> sl2(sl1);          // Copia

6. Construcción in-place

7. Intercambio de estructurasSkipList<int, int> sl3(std::move(sl1)); // Moveskip_list_implementation/- **Iteradores completos**: Forward iterators (const y mutable)├── SkipList.h      # Implementación de la clase SkipList

8. Comparadores personalizados

9. Rendimiento con conjuntos de datos grandes (10,000 elementos)



## Comparación con Estructuras Alternativas// Comparador personalizado├── SkipList.h       # Implementación completa (header-only)



### vs. std::map (Árbol Red-Black)SkipList<int, std::string, std::greater<int>> desc;



- Ventaja: Implementación más simple, sin necesidad de operaciones de rebalanceo complejas├── main.cpp         # Suite de 10 tests exhaustivos- **Exception safety**: Validación de parámetros y manejo de errores├── main.cpp        # Programa de demostración

- Ventaja: Mejor rendimiento en escenarios concurrentes

- Desventaja: Complejidad temporal no determinística (probabilística)// Emplace



### vs. std::unordered_map (Tabla Hash)sl.emplace(1, 5, 'X'); // Construye in-place├── README.md        # Este archivo



- Ventaja: Mantiene elementos ordenados, permite iteración en orden```

- Ventaja: No requiere función hash

- Desventaja: Búsqueda ligeramente más lenta en promedio└── COMPARACION.md   # Comparación detallada de características- **Const-correctness**: Métodos const apropiados└── README.md       # Este archivo



## Aplicaciones## Tests



Esta estructura de datos es particularmente adecuada para:```



- Implementación de índices en sistemas de bases de datos`main.cpp` incluye 10 tests que verifican todas las funcionalidades.

- Cachés con políticas de reemplazo basadas en orden

- Colas de prioridad en schedulers- **Type traits**: Validación en tiempo de compilación```

- Sistemas distribuidos que requieren sincronización eficiente

## Complejidad

## Referencias

## 🔧 Compilación

Pugh, W. (1990). "Skip Lists: A Probabilistic Alternative to Balanced Trees". *Communications of the ACM*, 33(6), 668-676.

| Operación | Promedio | Peor Caso |

## Autor

|-----------|----------|-----------|- **Compilación limpia**: Sin warnings con `-Wall -Wextra`

Luis Fernando

| Búsqueda/Inserción/Eliminación | O(log n) | O(n) |

## Licencia

| Espacio | O(n) | O(n log n) |### Requisitos

MIT License - Permitido uso académico y comercial



## Autor- Compilador C++11 o superior (g++, clang++, MSVC)## Compilación



Luis Fernando



## Licencia### Windows (MinGW/g++)### API Completa:



MIT License```powershell


g++ -o skiplist main.cpp -std=c++11 -Wall -Wextra- `insert()` / `emplace()` - Inserción eficiente### Windows (MinGW/g++)

./skiplist

```- `search()` / `contains()` - Búsqueda```bash



### Windows (MSVC)- `at()` / `operator[]` - Acceso tipo `std::map`g++ -o skiplist main.cpp -std=c++11

```powershell

cl /EHsc main.cpp /std:c++14- `remove()` / `erase()` - Eliminación./skiplist

./main.exe

```- `begin()` / `end()` - Iteradores```



### Linux/Mac- `size()` / `empty()` / `clear()` - Utilidades

```bash

g++ -o skiplist main.cpp -std=c++11 -Wall -Wextra- `swap()` - Intercambio eficiente### Windows (MSVC)

./skiplist

```- `display()` - Visualización para debugging```bash



## 💻 Ejemplos de Usocl /EHsc main.cpp /std:c++14



### Ejemplo Básico## 📁 Estructura del Proyecto./main.exe



```cpp```

#include "SkipList.h"

#include <iostream>```

#include <string>

skip_list_implementation/### Linux/Mac

int main() {

    // Crear una Skip List├── SkipList.h       # Implementación completa (header-only)```bash

    SkipList<int, std::string> sl;

    ├── main.cpp         # Suite de pruebas y demostracióng++ -o skiplist main.cpp -std=c++11

    // Insertar elementos

    sl.insert(5, "cinco");├── README.md        # Este archivo./skiplist

    sl.insert(10, "diez");

    sl.insert(3, "tres");└── COMPARACION.md   # Comparación de características```

    

    // Buscar elementos```

    std::string value;

    if (sl.search(5, value)) {## Uso

        std::cout << "Encontrado: " << value << std::endl;

    }## 🔧 Compilación y Uso

    

    // Verificar existencia```cpp

    if (sl.contains(10)) {

        std::cout << "10 existe" << std::endl;### Requisitos#include "SkipList.h"

    }

    - Compilador C++11 o superior

    // Eliminar elementos

    sl.remove(5);- g++, clang++, MSVC o similar// Crear una Skip List

    

    // Mostrar estructuraSkipList<int, string> skipList;

    sl.display();

    ### Compilar

    return 0;

}// Insertar elementos

```

#### Windows (MinGW/g++)skipList.insert(5, "cinco");

### Uso Avanzado - Estilo std::map

```powershellskipList.insert(10, "diez");

```cpp

// Usar como std::mapg++ -o skiplist main.cpp -std=c++11 -Wall -Wextra

SkipList<std::string, int> edades;

./skiplist// Buscar elementos

// operator[] para inserción/acceso

edades["Alice"] = 25;```string value;

edades["Bob"] = 30;

edades["Charlie"] = 22;if (skipList.search(5, value)) {



// Acceso seguro con at() (lanza excepción si no existe)#### Windows (MSVC)    cout << "Encontrado: " << value << endl;

try {

    int edad = edades.at("Alice");```powershell}

    std::cout << "Edad: " << edad << std::endl;

} catch (const std::out_of_range& e) {cl /EHsc main.cpp /std:c++14

    std::cout << "No encontrado" << std::endl;

}./main.exe// Eliminar elementos



// Iteradores```skipList.remove(5);

for (auto it = edades.begin(); it != edades.end(); ++it) {

    std::cout << it.key() << ": " << it.value() << std::endl;

}

```#### Linux/Mac// Verificar tamaño



### Comparador Personalizado```bashcout << "Tamaño: " << skipList.size() << endl;



```cppg++ -o skiplist main.cpp -std=c++11 -Wall -Wextra

// Orden descendente

SkipList<int, std::string, std::greater<int>> desc;./skiplist// Mostrar estructura

desc.insert(5, "cinco");

desc.insert(2, "dos");```skipList.display();

desc.insert(8, "ocho");

// Orden: 8, 5, 2```

```

## 💻 Ejemplos de Uso

### Copy y Move Semantics

## API Principal

```cpp

SkipList<int, std::string> sl1;### Ejemplo Básico

sl1.insert(1, "uno");

sl1.insert(2, "dos");### Constructor



SkipList<int, std::string> sl2(sl1);         // Copia profunda```cpp```cpp

SkipList<int, std::string> sl3(std::move(sl1)); // Movimiento eficiente

```#include "SkipList.h"SkipList(int maxLevel = 16, float probability = 0.5)



## 📊 API Completa#include <iostream>```



### Constructor#include <string>- `maxLevel`: Nivel máximo permitido



```cpp- `probability`: Probabilidad de promoción a niveles superiores (típicamente 0.5)

SkipList(int maxLevel = 16, 

         float probability = 0.5f,int main() {

         const Compare& comp = Compare())

```    // Crear una Skip List de int -> string### Métodos Públicos



**Parámetros:**    SkipList<int, std::string> sl;

- `maxLevel`: Nivel máximo permitido (1-32)

- `probability`: Probabilidad de promoción (0-1, típicamente 0.5)    | Método | Complejidad | Descripción |

- `comp`: Comparador personalizado

    // Insertar elementos|--------|-------------|-------------|

### Métodos Principales

    sl.insert(5, "cinco");| `insert(K key, V value)` | O(log n) | Inserta o actualiza un par clave-valor |

| Método | Complejidad | Descripción |

|--------|-------------|-------------|    sl.insert(10, "diez");| `search(K key, V& value)` | O(log n) | Busca una clave y retorna su valor |

| `insert(key, value)` | O(log n) | Inserta o actualiza |

| `emplace(key, args...)` | O(log n) | Construye e inserta in-place |    sl.insert(3, "tres");| `remove(K key)` | O(log n) | Elimina un elemento por clave |

| `search(key, value)` | O(log n) | Busca y retorna valor |

| `contains(key)` | O(log n) | Verifica existencia |    | `size()` | O(1) | Retorna el número de elementos |

| `at(key)` | O(log n) | Acceso seguro (lanza excepción) |

| `operator[](key)` | O(log n) | Acceso/inserción estilo mapa |    // Buscar elementos| `empty()` | O(1) | Verifica si la lista está vacía |

| `remove(key)` | O(log n) | Elimina elemento |

| `erase(key)` | O(log n) | Alias de remove() |    std::string value;| `clear()` | O(n) | Elimina todos los elementos |

| `size()` | O(1) | Número de elementos |

| `empty()` | O(1) | Verifica si está vacía |    if (sl.search(5, value)) {| `display()` | O(n) | Muestra la estructura (debug) |

| `clear()` | O(n) | Elimina todos los elementos |

| `swap(other)` | O(1) | Intercambia con otra lista |        std::cout << "Encontrado: " << value << std::endl;

| `display()` | O(n) | Muestra estructura (debug) |

    }## Complejidad Temporal

### Iteradores

    

```cpp

Iterator begin();              // Iterador mutable    // Verificar existencia| Operación | Promedio | Peor Caso |

Iterator end();

ConstIterator cbegin() const;  // Iterador constante    if (sl.contains(10)) {|-----------|----------|-----------|

ConstIterator cend() const;

```        std::cout << "10 existe" << std::endl;| Búsqueda  | O(log n) | O(n) |



## 🧪 Tests Incluidos    }| Inserción | O(log n) | O(n) |



El archivo `main.cpp` incluye 10 tests exhaustivos que verifican:    | Eliminación | O(log n) | O(n) |



1. ✅ Operaciones básicas (insert, search, remove)    // Eliminar elementos| Espacio   | O(n) | O(n log n) |

2. ✅ Copy & Move semantics

3. ✅ Iteradores y modificación de valores    sl.remove(5);

4. ✅ operator[] (estilo std::map)

5. ✅ at() con excepciones    ## Ventajas vs Árboles Balanceados

6. ✅ Exception safety y validaciones

7. ✅ emplace() (construcción in-place)    // Mostrar estructura

8. ✅ swap() entre listas

9. ✅ Comparador personalizado    sl.display();✅ Más simple de implementar

10. ✅ Dataset grande (10,000 elementos)

    ✅ No requiere rotaciones complejas

## ⚡ Complejidad

    return 0;✅ Excelente rendimiento en operaciones concurrentes

| Operación | Promedio | Peor Caso | Espacio |

|-----------|----------|-----------|---------|}✅ Código más fácil de entender y mantener

| Búsqueda  | O(log n) | O(n) | - |

| Inserción | O(log n) | O(n) | - |```

| Eliminación | O(log n) | O(n) | - |

| Espacio total | O(n) | O(n log n) | O(n) |## Ejemplo de Salida



## 🎯 Comparación con Otras Estructuras### Uso Avanzado - Estilo std::map



### vs std::map (Red-Black Tree)```

- ✅ Más simple de implementar

- ✅ Mejor rendimiento en operaciones concurrentes```cpp***** Skip List *****

- ✅ No requiere rebalanceo complejo

- ⚠️ Rendimiento probabilístico (no garantizado)// Usar como std::mapLevel 3: [9:Nueve] [21:Veintiuno]



### vs std::unordered_map (Hash Table)SkipList<std::string, int> edades;Level 2: [7:Siete] [9:Nueve] [21:Veintiuno]

- ✅ Mantiene elementos ordenados

- ✅ No requiere función hashLevel 1: [3:Tres] [7:Siete] [9:Nueve] [17:Diecisiete] [21:Veintiuno]

- ✅ Mejor para iteraciones ordenadas

- ⚠️ Búsqueda ligeramente más lenta en promedio// operator[] para inserción/accesoLevel 0: [3:Tres] [6:Seis] [7:Siete] [9:Nueve] [12:Doce] [17:Diecisiete] [19:Diecinueve] [21:Veintiuno] [25:Veinticinco] [26:Veintiseis]



## 🎓 Casos de Uso Idealesedades["Alice"] = 25;*********************



- **Sistemas de bases de datos**: Índices ordenadosedades["Bob"] = 30;```

- **Caches con LRU**: Acceso ordenado eficiente

- **Schedulers**: Colas de prioridadedades["Charlie"] = 22;

- **Sistemas distribuidos**: Fácil de implementar de forma concurrente

- **Aprendizaje**: Excelente para entender estructuras probabilísticas## Autor



## 📚 Recursos Adicionales// Acceso seguro con at() (lanza excepción si no existe)



- **COMPARACION.md**: Comparación detallada entre versión básica y robustatry {Luis Fernando

- William Pugh, "Skip Lists: A Probabilistic Alternative to Balanced Trees" (1990)

    int edad = edades.at("Alice");

## 👨‍💻 Autor

    std::cout << "Edad de Alice: " << edad << std::endl;## Licencia

Luis Fernando

} catch (const std::out_of_range& e) {

## 📄 Licencia

    std::cout << "No encontrado" << std::endl;MIT License

MIT License - Libre para uso educativo y comercial

}

---

// Iteradores

**¿Por qué usar Skip List?**for (auto it = edades.begin(); it != edades.end(); ++it) {

    std::cout << it.key() << ": " << it.value() << std::endl;

> "Si necesitas una estructura ordenada y el árbol balanceado te parece demasiado complejo, Skip List es tu mejor opción."}

```

---

### Copy y Move Semantics

Para más detalles técnicos, consulta la documentación inline en `SkipList.h`.

```cpp
// Constructor de copia
SkipList<int, std::string> sl1;
sl1.insert(1, "uno");
sl1.insert(2, "dos");

SkipList<int, std::string> sl2(sl1);  // Copia profunda

// Move constructor
SkipList<int, std::string> sl3(std::move(sl1));  // Movimiento eficiente
```

### Comparador Personalizado

```cpp
// Orden descendente
SkipList<int, std::string, std::greater<int>> desc;
desc.insert(5, "cinco");
desc.insert(2, "dos");
desc.insert(8, "ocho");

// Los elementos estarán en orden: 8, 5, 2
```

### Emplace (Construcción in-place)

```cpp
SkipList<int, std::string> sl;

// Construye el string in-place
sl.emplace(1, "Hello");
sl.emplace(2, 5, 'X');  // string(5, 'X') = "XXXXX"
```

## 📊 API Completa

### Constructor

```cpp
SkipList(int maxLevel = 16, 
         float probability = 0.5f,
         const Compare& comp = Compare())
```

- `maxLevel`: Nivel máximo permitido (1-32)
- `probability`: Probabilidad de promoción (0-1, típicamente 0.5)
- `comp`: Comparador personalizado

### Métodos Principales

| Método | Complejidad | Descripción |
|--------|-------------|-------------|
| `insert(key, value)` | O(log n) | Inserta o actualiza |
| `emplace(key, args...)` | O(log n) | Construye e inserta in-place |
| `search(key, value)` | O(log n) | Busca y retorna valor |
| `contains(key)` | O(log n) | Verifica existencia |
| `at(key)` | O(log n) | Acceso seguro (lanza excepción) |
| `operator[](key)` | O(log n) | Acceso/inserción estilo mapa |
| `remove(key)` | O(log n) | Elimina elemento |
| `erase(key)` | O(log n) | Alias de remove() |
| `size()` | O(1) | Número de elementos |
| `empty()` | O(1) | Verifica si está vacía |
| `clear()` | O(n) | Elimina todos los elementos |
| `swap(other)` | O(1) | Intercambia con otra lista |
| `display()` | O(n) | Muestra estructura (debug) |

### Iteradores

```cpp
Iterator begin();
Iterator end();
ConstIterator cbegin() const;
ConstIterator cend() const;
```

## 🧪 Tests Incluidos

El archivo `main.cpp` incluye 10 tests exhaustivos:

1. ✅ Operaciones básicas (insert, search, remove)
2. ✅ Copy & Move semantics
3. ✅ Iteradores y modificación de valores
4. ✅ operator[] (estilo std::map)
5. ✅ at() con excepciones
6. ✅ Exception safety y validaciones
7. ✅ emplace() (construcción in-place)
8. ✅ swap() entre listas
9. ✅ Comparador personalizado
10. ✅ Dataset grande (10,000 elementos)

## ⚡ Complejidad

| Operación | Promedio | Peor Caso | Espacio |
|-----------|----------|-----------|---------|
| Búsqueda  | O(log n) | O(n) | - |
| Inserción | O(log n) | O(n) | - |
| Eliminación | O(log n) | O(n) | - |
| Espacio total | O(n) | O(n log n) | O(n) |

## 🎯 Ventajas de esta Implementación

### vs Implementaciones Básicas:
- ✅ Thread-safe random generation (cada instancia tiene su generador)
- ✅ Se puede copiar y mover de forma segura
- ✅ Validación de parámetros y manejo de errores
- ✅ Interfaz compatible con STL
- ✅ Iteradores para usar con algoritmos STL

### vs std::map:
- ✅ Más simple de implementar
- ✅ Mejor rendimiento en inserciones concurrentes
- ✅ No requiere rebalanceo complejo
- ⚠️ Rendimiento probabilístico (no garantizado)

### vs std::unordered_map:
- ✅ Mantiene elementos ordenados
- ✅ No requiere función hash
- ✅ Mejor en iteraciones ordenadas
- ⚠️ Búsqueda ligeramente más lenta

## 📚 Recursos Adicionales

- `COMPARACION.md` - Comparación detallada de características
- William Pugh, "Skip Lists: A Probabilistic Alternative to Balanced Trees" (1990)

## 👨‍💻 Autor

Luis Fernando

## 📄 Licencia

MIT License - Libre para uso educativo y comercial

---

## 🎓 Casos de Uso Ideales

- **Sistemas de bases de datos**: Índices ordenados
- **Caches**: LRU con acceso ordenado
- **Schedulers**: Colas de prioridad
- **Sistemas distribuidos**: Fácil de implementar de forma concurrente
- **Aprendizaje**: Excelente para entender estructuras probabilísticas

---

**¿Por qué usar Skip List?**

> "Si necesitas una estructura ordenada y el árbol balanceado te parece demasiado complejo, Skip List es tu mejor opción."

---

Para preguntas o sugerencias, consulta la documentación inline en `SkipList.h`.
