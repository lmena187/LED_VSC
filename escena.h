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

// ============================================================
//  CUADRADO CON LADOS INDEPENDIENTES/SEPARADOS Y ESQUINAS
//  Estilo wireframe técnico con caracteres de esquina
// Las esquinas se dibujan por separado "└"
// ============================================================
//  FORMATO ANTIGUO DEL PATH, string normal en una línea,
// ============================================================

// Lado superior (horizontal, sin extremos)
Figura ladoSuperior;
ladoSuperior.path   = R"(M 8,0
H 24.000001)";
ladoSuperior.color  = Color::VERDE_MATRIX;
ladoSuperior.trazo  = "*";
ladoSuperior.grosor = 1;
ladoSuperior.ladoIndependiente  = true;
figuras.push_back(ladoSuperior);

// Lado inferior (horizontal, sin extremos)
Figura ladoInferior;
ladoInferior.path   = R"(M 24.000001,12
H 8)";
ladoInferior.color  = Color::VERDE_MATRIX;
ladoInferior.trazo  = "*";
ladoInferior.grosor = 1;
ladoInferior.ladoIndependiente = true;
figuras.push_back(ladoInferior);

// Lado izquierdo (vertical, sin extremos)
Figura ladoIzquierdo;
ladoIzquierdo.path   = R"(M 8,12
V 0)";
ladoIzquierdo.color  = Color::VERDE_MATRIX;
ladoIzquierdo.trazo  = "*";
ladoIzquierdo.grosor = 1;
ladoIzquierdo.ladoIndependiente = true;
figuras.push_back(ladoIzquierdo);

// Lado derecho (vertical, sin extremos)
Figura ladoDerecho;
ladoDerecho.path   = R"(M 24.000001,0
V 12)";
ladoDerecho.color  = Color::VERDE_MATRIX;
ladoDerecho.trazo  = "*";
ladoDerecho.grosor = 1;
ladoDerecho.ladoIndependiente = true;
figuras.push_back(ladoDerecho);


// ============================================================
//  DORMITORIO sin separar extremos, estilo mas solido, sin caracteres de esquina
// ============================================================

/*Figura cuartoSolido;
cuartoSolido.path   = R"(M 8.03545,0.03545061
H 23.964549
V 11.96455
H 8.03545
Z)";
cuartoSolido.color  = Color::ROJO;
cuartoSolido.trazo  = "*";
cuartoSolido.grosor = 1;
figuras.push_back(cuartoSolido);*/



  for (size_t i = 0; i < figuras.size(); i++) {
        pincel.color  = figuras[i].color;
        pincel.trazo  = figuras[i].trazo;
        pincel.grosor = figuras[i].grosor;
        //std::vector<Punto> verts = parseSVG(figuras[i].path);
        std::vector<Punto> verts = parseSVG(figuras[i].path, figuras[i].ladoIndependiente);
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
        tagsDinamicos.push_back({38, 7, "❶", Color::AMARILLO});
        tagsDinamicos.push_back({38, 8, "ON",  Color::AMARILLO});
    } else {
        limpiarPosicion(14, 8, 20);
        tagsDinamicos.push_back({38, 7, "❶",  Color::BLANCO_ROTO});
        tagsDinamicos.push_back({38, 8, "OFF", Color::BLANCO_ROTO});
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
        Color::VERDE_MATRIX);
    escribirEnPosicion(2, fila + 1,
        "  Tiempo ON       : " + formatearTiempo(tiempoMostrar) + "   ",
        Color::VERDE_MATRIX);
    escribirEnPosicion(2, fila + 2,
        "  Ultimo evento   : " + stats.ultimoEvento + "   ",
        Color::VERDE_MATRIX);
    escribirEnPosicion(2, fila + 3,
        "  --------------------------------   ",
        Color::VERDE_MATRIX);

    // Modo actual y teclas disponibles
    if (modoManualActivo) {
        escribirEnPosicion(2, fila + 4,
            "  Modo: MANUAL                       ",
            Color::AMARILLO, true);
        escribirEnPosicion(2, fila + 5,
            "  Teclas: 1=ON  0=OFF  A=Auto        ",
            Color::VERDE_MATRIX);
    } else {
        escribirEnPosicion(2, fila + 4,
            "  Modo: AUTOMATICO                   ",
            Color::ROJO, true);
        escribirEnPosicion(2, fila + 5,
            "  Teclas: M=Manual  A=Auto           ",
            Color::VERDE_MATRIX);
    } 

    // Prompt con ultima tecla presionada
    std::string teclaStr = (stats.ultimaTecla == ' ') ? " " : std::string(1, stats.ultimaTecla);
    escribirEnPosicion(2, fila + 6,
        "  > [" + teclaStr + "]                    ",
        Color::VERDE_MATRIX);

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

// ============================================================
//  ESCRIBIR TEXTO ESTATICO USANDO PIXELES Y ESCRIBIR EN POSICIONES FIJAS
// ============================================================

    pincel.color = Color::VERDE_MATRIX;
    setPixel(1, 15, ".");
    escribirTexto(1,         25, ".", Color::BLANCO);
    escribirTextoVertical(1, 10, ".", Color::BLANCO);

// ============================================================
//  ESQUINAS DEL RECTANGULO SEPARADO
// ============================================================
    /*pincel.color = Color::VERDE_MATRIX;
    setPixel(8, 0, "█");
    setPixel(24, 0, "█");
    setPixel(24, 6, "┘");
    setPixel(8, 6, "└");*/

    actualizarTagsDinamicos();
    imprimirCanvas();
    dibujarTags(tags);
    dibujarTags(tagsDinamicos);

    escribirEnPosicion(30, 2, "CONTROL ENERGETICO", Color::VERDE_MATRIX, true);
    mostrarEstadisticasYPrompt();
}