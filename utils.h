#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

// Convierte el nombre del mes a número (para orden cronológico si quisieras extender)
int mesAInt(const std::string& mes) {
    if (mes == "Jan") return 1;
    if (mes == "Feb") return 2;
    if (mes == "Mar") return 3;
    if (mes == "Apr") return 4;
    if (mes == "May") return 5;
    if (mes == "Jun") return 6;
    if (mes == "Jul") return 7;
    if (mes == "Aug") return 8;
    if (mes == "Sep") return 9;
    if (mes == "Oct") return 10;
    if (mes == "Nov") return 11;
    if (mes == "Dec") return 12;
    return 0;
}

// Extrae la IP sin puerto
std::string limpiarIP(const std::string& ipConPuerto) {
    size_t pos = ipConPuerto.find(':');
    return ipConPuerto.substr(0, pos);
}

// Formatea una fecha completa tipo log
std::string formatearFecha(const std::string& mes, const std::string& dia, const std::string& hora) {
    std::ostringstream ss;
    ss << mes << " " << dia << " " << hora;
    return ss.str();
}

#endif
