// ============================================================
//  escena.h — Diseno visual y orquestacion de capas
//  Para cambiar el diseno visual — editar solo este archivo.
// ============================================================
#pragma once

#include "config.h"
#include "canvas.h"
#include "estadisticas.h"
#include "braille.h"   // <--- AGREGAR ESTA LÍNEA


// ============================================================
//  CONSTRUIR FIGURAS SVG
// ============================================================
inline void construirFiguras() {
    std::vector<Figura> figuras;


// ============================================================
//  VEREDA (2 lados independientes)
// ============================================================

// ============================================================
//  RECTÁNGULO ANCHO (desplazado -20 en X)
// ============================================================

Figura rectanguloAncho;
rectanguloAncho.path   = "M 0,0 H 79.000001 V 54.000002 H 0 Z";
rectanguloAncho.color  = Color::VERDE_MATRIX;
rectanguloAncho.trazo  = "█";
rectanguloAncho.grosor = 1;
rectanguloAncho.ladoIndependiente = false;
figuras.push_back(rectanguloAncho);



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
        tagsDinamicos.push_back({57, 7, "❶", Color::AMARILLO});
        tagsDinamicos.push_back({57,8, "ON",  Color::AMARILLO});
    } else {
        limpiarPosicion(14, 8, 20);
        tagsDinamicos.push_back({57, 7, "❶",  Color::BLANCO_ROTO});
        tagsDinamicos.push_back({57, 8, "OFF", Color::BLANCO_ROTO});
    }
}

// ============================================================
//  MOSTRAR ESTADISTICAS Y PROMPT
// ============================================================
inline void mostrarEstadisticasYPrompt() {
    // fila base del bloque de estadisticas
    // para mover todo el bloque cambia cfg.filaStats en config.h
    int fila = cfg.filaInicio + H + cfg.filaStats;

    std::string teclaStr = (stats.ultimaTecla == ' ') ? " " : std::string(1, stats.ultimaTecla);

    // Linea 1 — modo actual y teclas disponibles
    if (modoManualActivo) {
          escribirEnPosicion(2, fila,
            "  Modo: MANUAL     Teclas: 1=ON  0=OFF  A=AUTO  R=Reporte",
            Color::VERDE_MATRIX, true);
    } else {
       escribirEnPosicion(2, fila,
            "  Modo: AUTOMATICO    Teclas: M=Manual  A=Auto  R=Reporte",
            Color::VERDE_MATRIX, true);
    }

    // Linea 2 — prompt con ultima tecla presionada
    escribirEnPosicion(2, fila + 1,
        "  > [" + teclaStr + "]                    ",
        Color::VERDE_MATRIX);

    // Cursor al final del prompt
    std::cout << "\033[" << (fila + 1) << ";8H";
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
    
    escribirTexto(33,         29, "AV ESMERALDAS", Color::VERDE_MATRIX);
 
    actualizarTagsDinamicos();
    imprimirCanvas();
    dibujarTags(tags);
    dibujarTags(tagsDinamicos);
   
   
    // ============================================================
    //  CABECERA PRINCIPAL
    // ============================================================
    
    escribirEnPosicion(45, 1, "       AKI 812 LA CONCORDIA       ", Color::VERDE_MATRIX, true);
    escribirEnPosicion(45, 2, "══════════════════════════════════", Color::VERDE_MATRIX, false);
   
    
// ============================================================
//  DIBUJO DE BRAILLE POR CONJUNTO VERTICAL (varios caracteres a la vez)
//  Se encienden todos los puntos de una región rectangular
//  y luego se vuelca el canvas a la terminal.
// ============================================================

// Primero: limpio el canvas virtual para empezar desde cero
limpiarBraille();

// Segundo: enciendo TODOS los píxeles de una región de 2 columnas × 12 filas de píxeles.
//         12 píxeles de alto = 12 / 4 = 3 caracteres Braille verticales.
for (int y = 0; y < 12; y++) {
    for (int x = 0; x < BRAILLE_PIXEL_W; x++) {
        setPixelBraille(x, y);   // enciendo el punto (x, y)
    }
}

// Tercero: muestro el canvas completo en la terminal,
//          en la fila 4, columna 39, con color verde matrix.
imprimirBraille(7, 39, Color::VERDE_MATRIX);

       // ============================================================
       //   DIBUJAR BRAILLE INDIVIDUAL.
       // ============================================================
  
     bool ladrilloAmarillo1[8] = {1,1,1,1,1,1,1,1}; // /Aui defino el patrón ⠿
     dibujarCaracterBraille(21, 36, ladrilloAmarillo1, Color::VERDE_MATRIX); // Aqui dibujo el patron previamente establecdio
    
     
mostrarEstadisticasYPrompt();
 
}
