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
ladoSuperior.path   = "M 9,0 H 23";
ladoSuperior.color  = Color::VERDE_MATRIX;
ladoSuperior.trazo  = "─";
ladoSuperior.grosor = 1;
figuras.push_back(ladoSuperior);

// Lado inferior (horizontal, sin extremos)
Figura ladoInferior;
ladoInferior.path   = "M 23,6 H 9";
ladoInferior.color  = Color::VERDE_MATRIX;
ladoInferior.trazo  = "─";
ladoInferior.grosor = 1;
figuras.push_back(ladoInferior);

// Lado izquierdo (vertical, sin extremos)
Figura ladoIzquierdo;
ladoIzquierdo.path   = "M 8,5 V 1";
ladoIzquierdo.color  = Color::VERDE_MATRIX;
ladoIzquierdo.trazo  = "│";
ladoIzquierdo.grosor = 1;
figuras.push_back(ladoIzquierdo);

// Lado derecho (vertical, sin extremos)
Figura ladoDerecho;
ladoDerecho.path   = "M 24,1 V 10";
ladoDerecho.color  = Color::VERDE_MATRIX;
ladoDerecho.trazo  = "│";
ladoDerecho.grosor = 1;
figuras.push_back(ladoDerecho);


// ============================================================
//  CERRAMIENTO DE LA CASA (estructura principal)
//  Cuadrado que delimita el perímetro de la casa
// ============================================================
// ============================================================
//  FORMATO MODERNO DEL PATH,  raw string literal (R"(...)"), En formato multilínea
// ============================================================

// Lado superior (horizontal) - CERRAMIENTO
Figura cerramientoSuperior;
cerramientoSuperior.path = R"(M 0,0
                              H 50)";
cerramientoSuperior.color  = Color::VERDE_MATRIX;
cerramientoSuperior.trazo  = "█";
cerramientoSuperior.grosor = 1;
figuras.push_back(cerramientoSuperior);

// Lado inferior (horizontal) - CERRAMIENTO
Figura cerramientoInferior;
cerramientoInferior.path = R"(M 36,20
                              H 1)";
cerramientoInferior.color  = Color::VERDE_MATRIX;
cerramientoInferior.trazo  = "█";
cerramientoInferior.grosor = 1;
figuras.push_back(cerramientoInferior);

// Lado izquierdo (vertical) - CERRAMIENTO
Figura cerramientoIzquierdo;
cerramientoIzquierdo.path = R"(M 0,20
                              V 1)";
cerramientoIzquierdo.color  = Color::VERDE_MATRIX;
cerramientoIzquierdo.trazo  = "█";
cerramientoIzquierdo.grosor = 1;
figuras.push_back(cerramientoIzquierdo);

// Lado derecho (vertical) - CERRAMIENTO
Figura cerramientoDerecho;
cerramientoDerecho.path = R"(M 50,1
                              V 38)";
cerramientoDerecho.color  = Color::VERDE_MATRIX;
cerramientoDerecho.trazo  = "█";
cerramientoDerecho.grosor = 1;
figuras.push_back(cerramientoDerecho);

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
    pincel.color = Color::VERDE_MATRIX;
    setPixel(8, 0, "█");
    setPixel(24, 0, "█");
    setPixel(24, 6, "┘");
    setPixel(8, 6, "└");

    actualizarTagsDinamicos();
    imprimirCanvas();
    dibujarTags(tags);
    dibujarTags(tagsDinamicos);

    escribirEnPosicion(30, 2, "CONTROL ENERGETICO", Color::VERDE_MATRIX, true);
    mostrarEstadisticasYPrompt();
}