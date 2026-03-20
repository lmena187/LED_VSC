// ============================================================
//  config.h — Colores, structs y variables globales
// ============================================================
#pragma once

#include <atomic>
#include <mutex>
#include <vector>
#include <string>
#include <array>

const int W = 40;
const int H = 26;

namespace Color {
    const int RESET          = 0;
    const int NEGRO          = 30;
    const int BLANCO         = 37;
    const int BLANCO_INTENSO = 255;
    const int BLANCO_ROTO    = 253;
    const int GRIS_CLARO     = 250;
    const int AMARILLO       = 226;
    const int AMARILLO_ROTO  = 220;
    const int ROJO = 196;
}

struct TamanoTerminal { int columnas; int filas; };
struct Punto          { int x, y; };

struct Figura {
    std::string  path;
    int          color;
    const char*  trazo;
    int          grosor;
};

struct EmojiTag {
    int         x, y;
    std::string valor;
    int         color;
    bool        tieneFondo;
    int         colorFondo;
    EmojiTag(int x, int y, std::string valor, int color,
             bool tieneFondo = false, int colorFondo = Color::NEGRO)
        : x(x), y(y), valor(valor), color(color),
          tieneFondo(tieneFondo), colorFondo(colorFondo) {}
};

struct Config {
    bool usarColores       = true;
    bool mostrarPuntos     = false;
    int  colInicio         = 2;
    int  filaInicio        = 3;
};

struct Estado {
    std::atomic<int> led{0};
    std::atomic<int> socket{-1};
    std::mutex       mutexDibujo;
};

struct Pincel {
    int         color  = Color::BLANCO;
    const char* trazo  = "*";
    int         grosor = 1;
};

// ============================================================
//  ESTADISTICAS — uso del LED en memoria
// ============================================================
struct Estadisticas {
    int         vecesEncendido   = 0;
    int         segundosEncendido = 0;
    time_t      tiempoEncendido  = 0;
    bool        estaEncendido    = false;
    std::string ultimoEvento     = "---";
    char        ultimaTecla      = ' ';
};

extern Config        cfg;
extern Estado        estado;
extern Pincel        pincel;
extern Estadisticas  stats;

extern std::array<char, 4> canvas[H][W];
extern int                 canvasColor[H][W];

extern std::vector<EmojiTag> tags;
extern std::vector<EmojiTag> tagsDinamicos;

extern bool modoManualActivo;