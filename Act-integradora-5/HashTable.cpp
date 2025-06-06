/*
Autor: Samuel Rincón
Fecha: 6/5/2025
Fuentes:
1. Knuth, D. E. (1998). *The Art of Computer Programming Vol. 3: Sorting and Searching*. Addison-Wesley.
2. LaFore, R. (2002). *Data Structures and Algorithms in C++*. SAMS Publishing.
3. TutorialsPoint. (2024). [C++ Hash Tables](https://www.tutorialspoint.com/cplusplus/cpp_hash_tables.htm)
4. GeeksforGeeks. (2023). [Quadratic Probing in Hashing](https://www.geeksforgeeks.org/implementing-quadratic-probing-hash-table/)
5. cppreference.com. (2025). [std::overflow_error](https://en.cppreference.com/w/cpp/error/overflow_error)
*/

#include "HashTable.h"
#include <functional>
#include <stdexcept>

HashTable::HashTable(int s) : size(s), colisiones(0) {
    table.resize(size);
    ocupado.resize(size, false);
}

int HashTable::hash(const std::string &key, int i) const {
    std::hash<std::string> hashFunc;
    return (hashFunc(key) + i * i) % size;
}

bool HashTable::add(const IPSummary &ipSum) {
    for (int i = 0; i < size; ++i) {
        int idx = hash(ipSum.getIP(), i);
        if (!ocupado[idx]) {
            table[idx] = ipSum;
            ocupado[idx] = true;
            if (i > 0) colisiones++;
            return true;
        } else if (table[idx].getIP() == ipSum.getIP()) {
            return false; 
        }
    }
    throw std::overflow_error("Tabla Hash llena");
}

IPSummary HashTable::find(const std::string &ip) const {
    for (int i = 0; i < size; ++i) {
        int idx = hash(ip, i);
        if (!ocupado[idx]) break;
        if (table[idx].getIP() == ip) return table[idx];
    }
    throw std::runtime_error("IP no encontrada");
}

int HashTable::getColisiones() const {
    return colisiones;
}
