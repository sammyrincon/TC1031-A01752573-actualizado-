/*
 * Actividad Integradora 3 - TC1031
 * Autor: Javier Rincón V. - A01752573
 *
 * Instrucciones para compilar:
 *   g++ -std=c++17 -Wall -O3 -o main main.cpp
 * Instrucciones para ejecutar:
 *   ./main
 *
 * Fuentes:
 * - https://www.geeksforgeeks.org/heap-sort/
 * - https://cplusplus.com/reference/queue/priority_queue/
 * - https://www.digitalocean.com/community/tutorials/priority-queue-in-cpp-stl
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

// =================== ESTRUCTURA DE DATOS ====================
struct Registro {
    std::string mes, dia, hora, ipCompleta, razon;

    std::string getIP() const {
        return ipCompleta.substr(0, ipCompleta.find(':'));
    }

    std::string toString() const {
        return mes + " " + dia + " " + hora + " " + ipCompleta + " " + razon;
    }
};

struct AccesoIP {
    std::string ip;
    int cantidad;

    bool operator<(const AccesoIP& other) const {
        return cantidad < other.cantidad; // Para MaxHeap
    }
};

// =================== FUNCIONES AUXILIARES ====================
void heapify(std::vector<Registro>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].getIP() > arr[largest].getIP()) largest = l;
    if (r < n && arr[r].getIP() > arr[largest].getIP()) largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<Registro>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void leerBitacora(const std::string& nombreArchivo, std::vector<Registro>& registros) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        std::istringstream ss(linea);
        Registro r;
        ss >> r.mes >> r.dia >> r.hora >> r.ipCompleta;
        getline(ss, r.razon);
        registros.push_back(r);
    }
    archivo.close();
}

void guardarArchivo(const std::string& nombre, const std::vector<Registro>& registros) {
    std::ofstream out(nombre);
    for (const auto& r : registros) {
        out << r.toString() << std::endl;
    }
    out.close();
}

void contarIPs(const std::vector<Registro>& registros, std::priority_queue<AccesoIP>& heap) {
    std::map<std::string, int> contador;
    for (const auto& r : registros) {
        contador[r.getIP()]++;
    }

    for (const auto& par : contador) {
        heap.push(AccesoIP{par.first, par.second});
    }
}

void imprimirTop10(std::priority_queue<AccesoIP> heap) {
    std::ofstream out("ips_con_mayor_acceso.txt");
    for (int i = 0; i < 10 && !heap.empty(); ++i) {
        auto top = heap.top();
        std::cout << top.ip << " - " << top.cantidad << " accesos" << std::endl;
        out << top.ip << " - " << top.cantidad << " accesos" << std::endl;
        heap.pop();
    }
    out.close();
}

void encontrarMenor3(const std::priority_queue<AccesoIP>& heap) {
    auto temp = heap;
    AccesoIP resultado;
    bool encontrado = false;
    while (!temp.empty()) {
        auto actual = temp.top();
        if (actual.cantidad >= 3) {
            resultado = actual;
            encontrado = true;
        }
        temp.pop();
    }

    if (encontrado) {
        std::cout << "IP con menor numero de accesos (>=3): " 
                  << resultado.ip << " - " << resultado.cantidad << std::endl;
    } else {
        std::cout << "No se encontro ninguna IP con accesos >= 3" << std::endl;
    }
}

// =================== MAIN ====================
int main() {
    std::vector<Registro> registros;
    leerBitacora("bitacoraHeap.txt", registros);

    heapSort(registros);
    guardarArchivo("bitacora_ordenada.txt", registros);

    std::priority_queue<AccesoIP> heap;
    contarIPs(registros, heap);

    std::cout << "=== Top 10 IPs con mas accesos ===" << std::endl;
    imprimirTop10(heap);

    std::cout << "\n=== IP con menor numero de accesos (>=3) ===" << std::endl;
    encontrarMenor3(heap);

    return 0;
}
