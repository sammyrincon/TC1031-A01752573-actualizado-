/*
Autor: Samuel Rincón
Fecha: 6/5/2025
Fuentes:
1. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
2. ISO/IEC. (2011). *Information technology – Programming languages – C++* (ISO/IEC 14882:2011).
3. Bjarne Stroustrup. (2013). *The C++ Programming Language* (4th ed.). Addison-Wesley.
4. cppreference.com. (2025). [std::map](https://en.cppreference.com/w/cpp/container/map)
5. GeeksforGeeks. (2024). [Reading files in C++ line by line](https://www.geeksforgeeks.org/different-ways-reading-text-file-cpp/)

INSTRUCCIONES DE COMPILACION:
  g++ -std=c++11 -Wall -o programa.exe main.cpp HashTable.cpp IPSummary.cpp

INSTRUCCIONES DE EJECUCION:

    ./progrma.exe (poweshell)

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "HashTable.h"

void procesarBitacora(const std::string &filename, HashTable &tabla, std::map<std::string, int> &entrantes) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo.\n";
        return;
    }

    int n, m;
    file >> n >> m;
    file.ignore();

    std::vector<std::string> ips(n);
    for (int i = 0; i < n; ++i) {
        std::getline(file, ips[i]);
    }

    std::map<std::string, IPSummary> resumenes;

    for (int i = 0; i < m; ++i) {
        std::string linea;
        std::getline(file, linea);
        std::istringstream ss(linea);
        std::string mes, dia, hora, ipOrigen, ipDestino;
        int peso;
        std::string motivo;

        ss >> mes >> dia >> hora >> ipOrigen >> ipDestino >> peso;
        std::getline(ss, motivo);

        std::string ipO = ipOrigen.substr(0, ipOrigen.find(":"));
        std::string ipD = ipDestino.substr(0, ipDestino.find(":"));

        if (resumenes.find(ipO) == resumenes.end())
            resumenes[ipO] = IPSummary(ipO);
        if (resumenes.find(ipD) == resumenes.end())
            resumenes[ipD] = IPSummary(ipD);

        resumenes[ipO].addDestino(ipD);
        entrantes[ipD]++;
    }

    for (auto &par : resumenes) {
        par.second.setEntrantes(entrantes[par.first]);
        tabla.add(par.second);
    }
}


void getIPSummary(HashTable &tabla) {
    std::string ip;
    std::cout << "Ingresa la IP: ";
    std::cin >> ip;
    try {
        IPSummary resumen = tabla.find(ip);
        std::cout << resumen.toString();
        std::vector<std::string> destinos = resumen.getDestinosOrdenadosDesc();
        std::cout << "Lista de direcciones accesadas:\n";
        for (const auto &d : destinos)
            std::cout << d << "\n";
    } catch (...) {
        std::cout << "IP no encontrada\n";
    }
}

int main() {
    std::string archivo = "bitacoraGrafos.txt";
    int tamanoTabla = 20011; //numero primo
    HashTable tabla(tamanoTabla);
    std::map<std::string, int> entrantes;

    procesarBitacora(archivo, tabla, entrantes);

    std::cout << "Colisiones: " << tabla.getColisiones() << "\n";

    getIPSummary(tabla);

    return 0;
}
