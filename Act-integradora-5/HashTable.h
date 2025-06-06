/*
Autor: Samuel Rincón
Fecha: 6/5/2025
Fuentes:
1. Weiss, M. A. (2014). *Data Structures and Algorithm Analysis in C++* (4th ed.). Pearson.
2. Sahni, S. (2005). *Data Structures, Algorithms, and Applications in C++* (2nd ed.). Silicon Press.
3. cppreference.com. (2025). [std::vector](https://en.cppreference.com/w/cpp/container/vector)
4. GeeksforGeeks. (2024). [Hashing – Open Addressing](https://www.geeksforgeeks.org/open-addressing-collision-handling-technique/)
5. GNU C++ Library Manual. (2025). [std::hash](https://gcc.gnu.org/onlinedocs/libstdc++/manual/)
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "IPSummary.h"
#include <vector>
#include <string>

class HashTable {
private:
    std::vector<IPSummary> table;
    std::vector<bool> ocupado;
    int size;
    int colisiones;

    int hash(const std::string &key, int i) const;

public:
    HashTable(int s);
    bool add(const IPSummary &ipSum);
    IPSummary find(const std::string &ip) const;
    int getColisiones() const;
};

#endif
