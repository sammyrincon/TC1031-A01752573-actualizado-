/*
Autor: Samuel Rincón
Fecha: 6/5/2025
Fuentes:
1. C++ Core Guidelines. (2025). [Encapsulation and class design](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
2. cppreference.com. (2025). [std::string](https://en.cppreference.com/w/cpp/string/basic_string)
3. Microsoft Docs. (2024). [C++ class definition syntax](https://learn.microsoft.com/en-us/cpp/cpp/classes-cpp)
4. GeeksforGeeks. (2023). [Sorting a vector in C++](https://www.geeksforgeeks.org/sort-c-stl/)
5. ISO/IEC. (2011). *C++ Standard Library*. ISO/IEC 14882.
*/

#ifndef IPSUMMARY_H
#define IPSUMMARY_H

#include <string>
#include <vector>
#include <algorithm>

class IPSummary {
private:
    std::string ip;
    std::vector<std::string> destinos;
    int entrantes;

public:
    IPSummary() : ip(""), entrantes(0) {}
    IPSummary(const std::string &ip) : ip(ip), entrantes(0) {}

    std::string getIP() const { return ip; }

    void addDestino(const std::string &dest) { destinos.push_back(dest); }

    void setEntrantes(int count) { entrantes = count; }

    int getEntrantes() const { return entrantes; }

    int getSalientes() const { return destinos.size(); }

    double getRelacion() const {
        return (entrantes == 0) ? getSalientes() : (double)getSalientes() / entrantes;
    }

    std::vector<std::string> getDestinosOrdenadosDesc() const {
        std::vector<std::string> copia = destinos;
        std::sort(copia.rbegin(), copia.rend());
        return copia;
    }

    std::string toString() const;
};

#endif
