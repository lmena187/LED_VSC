// ============================================================
//  escena.h — Diseno visual y orquestacion de capas
//  Para cambiar el diseno visual — editar solo este archivo.
// ============================================================
#pragma once

#include "config.h"
#include "canvas.h"
#include "estadisticas.h"

// ============================================================
//  CONSTRUIR FIGURAS SVG
// ============================================================
inline void construirFiguras() {
    std::vector<Figura> figuras;

    // Figura 1: Techo de la casa
    Figura fig1;
    fig1.path   = "M 5.049696,0.04985034  V 8.9684027  H 24.987577"
                  "  V 10.950304  H 36.950304  V 0.14825567  Z";
    fig1.color  = Color::GRIS_CLARO;
    fig1.trazo  = "█";
    fig1.grosor = 1;
    figuras.push_back(fig1);

    for (size_t i = 0; i < figuras.size(); i++) {
        pincel.color  = figuras[i].color;
        pincel.trazo  = figuras[i].trazo;
        pincel.grosor = figuras[i].grosor;
        std::vector<Punto> verts = parseSVG(figuras[i].path);
        for (size_t j = 0; j+1 < verts.size(); j++)
            line(verts[j].x, verts[j].y, verts[j+1].x, verts[j+1].y);
    }
}

// ============================================================
//  ACTUALIZAR TAGS DINAMICOS
// ============================================================
inline void actualizarTagsDinamicos() {
    tagsDinamicos.clear();
    if (estado.led.load() == 1) {
        limpiarPosicion(14, 8, 20);
        tagsDinamicos.push_back({17, 7, "❶", Color::AMARILLO});
        tagsDinamicos.push_back({17, 8, "ON",  Color::AMARILLO});
    } else {
        limpiarPosicion(14, 8, 20);
        tagsDinamicos.push_back({18, 7, "❶",  Color::BLANCO_ROTO});
        tagsDinamicos.push_back({17, 8, "OFF", Color::BLANCO_ROTO});
    }
}

// ============================================================
//  MOSTRAR ESTADISTICAS Y PROMPT
// ============================================================
inline void mostrarEstadisticasYPrompt() {
    int tiempoMostrar = stats.segundosEncendido;
    if (stats.estaEncendido)
        tiempoMostrar += (int)(time(nullptr) - stats.tiempoEncendido);

    int fila = cfg.filaInicio + H + 1;

    escribirEnPosicion(2, fila,
        "  Veces encendido : " + std::to_string(stats.vecesEncendido) + "   ",
        Color::BLANCO_ROTO);
    escribirEnPosicion(2, fila + 1,
        "  Tiempo ON       : " + formatearTiempo(tiempoMostrar) + "   ",
        Color::BLANCO_ROTO);
    escribirEnPosicion(2, fila + 2,
        "  Ultimo evento   : " + stats.ultimoEvento + "   ",
        Color::BLANCO_ROTO);
    escribirEnPosicion(2, fila + 3,
        "  --------------------------------   ",
        Color::BLANCO_ROTO);

    // Modo actual y teclas disponibles
    if (modoManualActivo) {
        escribirEnPosicion(2, fila + 4,
            "  Modo: MANUAL                       ",
            Color::AMARILLO, true);
        escribirEnPosicion(2, fila + 5,
            "  Teclas: 1=ON  0=OFF  A=Auto        ",
            Color::BLANCO_ROTO);
    } else {
        escribirEnPosicion(2, fila + 4,
            "  Modo: AUTOMATICO                   ",
            Color::GRIS_CLARO, true);
        escribirEnPosicion(2, fila + 5,
            "  Teclas: M=Manual  A=Auto           ",
            Color::BLANCO_ROTO);
    }

    // Prompt con ultima tecla presionada
    std::string teclaStr = (stats.ultimaTecla == ' ') ? " " : std::string(1, stats.ultimaTecla);
    escribirEnPosicion(2, fila + 6,
        "  > [" + teclaStr + "]                    ",
        Color::BLANCO_INTENSO);

    // Cursor al final del prompt
    std::cout << "\033[" << (fila + 6) << ";8H";
    std::cout.flush();
}

// ============================================================
//  CONSTRUIR Y DIBUJAR
// ============================================================
inline void construirYDibujar() {
    clearCanvas();
    construirFiguras();

    pincel.color = Color::BLANCO;
    setPixel(1, 15, ".");
    escribirTexto(1,         25, ".", Color::BLANCO);
    escribirTextoVertical(1, 10, ".", Color::BLANCO);

    actualizarTagsDinamicos();
    imprimirCanvas();
    dibujarTags(tags);
    dibujarTags(tagsDinamicos);

    escribirEnPosicion(15, 1, "CONTROL ENERGETICO", Color::BLANCO, true);
    mostrarEstadisticasYPrompt();
}