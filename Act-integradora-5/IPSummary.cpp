/*
Autor: Samuel Rincón
Fecha: 6/5/2025
Fuentes:
1. cppreference.com. (2025). [std::ostringstream](https://en.cppreference.com/w/cpp/io/basic_ostringstream)
2. GeeksforGeeks. (2024). [Vector operations in C++](https://www.geeksforgeeks.org/vector-in-cpp-stl/)
3. Stroustrup, B. (2013). *Programming: Principles and Practice Using C++* (2nd ed.). Addison-Wesley.
4. IBM Documentation. (2023). [C++ I/O Streams](https://www.ibm.com/docs/en/zos/2.4.0?topic=programs-c-inputoutput-streams)
5. ModernesCpp.com. (2024). [Generating custom string output in C++](https://www.modernescpp.com/index.php/std-stringstreams)
*/

#include "IPSummary.h"
#include <sstream>

std::string IPSummary::toString() const {
    std::ostringstream oss;
    oss << "IP: " << ip << "\n";
    oss << "Total de direcciones que intentaron acceder a la IP: " << entrantes << "\n";
    oss << "Total de direcciones accesadas desde la IP: " << getSalientes() << "\n";
    oss << "Relacion entre el numero de direcciones accesadas y que intentaron acceder a la IP: " << getRelacion() << "\n";
    return oss.str();
}
