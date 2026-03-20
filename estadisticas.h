// ============================================================
//  estadisticas.h — Registro de uso del LED
//  Version minimalista: solo memoria, sin archivos.
// ============================================================
#pragma once

#include "config.h"
#include <ctime>
#include <sstream>
#include <iomanip>

inline std::string formatearTiempo(int segundos) {
    int h = segundos / 3600;
    int m = (segundos % 3600) / 60;
    int s = segundos % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << h << ":"
        << std::setfill('0') << std::setw(2) << m << ":"
        << std::setfill('0') << std::setw(2) << s;
    return oss.str();
}

inline std::string horaActual() {
    time_t ahora = time(nullptr);
    struct tm* t = localtime(&ahora);
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << t->tm_hour << ":"
        << std::setfill('0') << std::setw(2) << t->tm_min  << ":"
        << std::setfill('0') << std::setw(2) << t->tm_sec;
    return oss.str();
}

inline void registrarEvento(int nuevoEstado) {
    time_t ahora = time(nullptr);
    if (nuevoEstado == 1 && !stats.estaEncendido) {
        stats.vecesEncendido++;
        stats.tiempoEncendido = ahora;
        stats.estaEncendido   = true;
        stats.ultimoEvento    = "ENCENDIDO " + horaActual();
    } else if (nuevoEstado == 0 && stats.estaEncendido) {
        stats.segundosEncendido += (int)(ahora - stats.tiempoEncendido);
        stats.estaEncendido      = false;
        stats.ultimoEvento       = "APAGADO   " + horaActual();
    }
}