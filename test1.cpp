#include "SkipList.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main(){
    SkipList<int,string> sl;
    sl.insert(5, "cinco");
    sl.insert(6, "cinco");
    sl.insert(10, "diez");
    sl.insert(3, "tres");
    sl.insert(7, "siete");
    sl.insert(11, "cinco");
    sl.insert(2, "diez");
    sl.insert(1, "tres");
    sl.insert(8, "siete");
    sl.insert(12, "cinco");
    sl.insert(4, "diez");
    sl.insert(9, "tres");
    sl.insert(13, "siete");
    sl.display();


    SkipList<int, string> sl2(sl);
    cout << "Copia creada. Size: " << sl2.size() << endl;
    sl2.display();

    SkipList<int, string> sl3(sl);
    cout << "Copia creada. Size: " << sl3.size() << endl;
    sl3.display();

    SkipList<int, string> sl4(sl);
    cout << "Copia creada. Size: " << sl4.size() << endl;
    sl4.display();

    SkipList<int, string> sl5(sl);
    cout << "Copia creada. Size: " << sl5.size() << endl;
    sl5.display();

    SkipList<int, string> sl6(sl);
    cout << "Copia creada. Size: " << sl6.size() << endl;
    sl6.display();

    SkipList<int, string> sl7(sl);
    cout << "Copia creada. Size: " << sl7.size() << endl;
    sl7.display();

    SkipList<int, string> sl8(sl);
    cout << "Copia creada. Size: " << sl8.size() << endl;
    sl8.display();

    cout << "Llego" << endl; 
}