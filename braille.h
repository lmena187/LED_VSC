// ============================================================
//  braille.h — Canvas Braille independiente (buffer de píxeles)
//  No modifica ni interfiere con el canvas existente.
// ============================================================
#pragma once

#include <cstdint>
#include <cstdlib>   // para abs()
#include <iostream>  // para std::cout
#include <string>    // para std::string
#include <cwchar>    // para wctomb

#include "config.h"  // para Color
#include "canvas.h"  // para escribirEnPosicion

// ============================================================
//  CONSTANTES DE DIMENSIÓN
// ============================================================

// Dimensiones en píxeles (resolución de dibujo)
const int BRAILLE_PIXEL_W = 2;   //2 píxeles de ancho, debe ser múltiplo de 2 para que quepa exactamente en caracteres Braille
const int BRAILLE_PIXEL_H = 68;   // 68 píxeles de alto, debe ser múltiplo de 4 para que quepa exactamente en caracteres Braille

// Dimensiones en caracteres Braille (se calculan automáticamente)
// Cada carácter Braille tiene: 2 columnas × 4 filas
const int BRAILLE_CHAR_W = BRAILLE_PIXEL_W / 2;   // = 1 caracteres de ancho
const int BRAILLE_CHAR_H = BRAILLE_PIXEL_H / 4;   // = 17 caracteres de alto

// ============================================================
//  BUFFER DE PÍXELES (1 bit por píxel)
// ============================================================

// Calculamos cuántos bytes necesitamos por fila: 80 píxeles / 8 = 10 bytes por fila
//const int BRAILLE_BYTES_POR_FILA = BRAILLE_PIXEL_W / 8;   // = 10
const int BRAILLE_BYTES_POR_FILA = (BRAILLE_PIXEL_W + 7) / 8;  // division entera hacia arriba — escala con BRAILLE_PIXEL_W
// Buffer de píxeles: 28 filas × 10 bytes por fila = 280 bytes totales
// Cada bit representa un píxel (1 = encendido, 0 = apagado)
static uint8_t braillePixels[BRAILLE_PIXEL_H][BRAILLE_BYTES_POR_FILA];

// ============================================================
//  FUNCIONES BÁSICAS
// ============================================================

// Limpiar todo el canvas Braille (todos los píxeles a 0)
inline void limpiarBraille() {
    for (int y = 0; y < BRAILLE_PIXEL_H; y++) {
        for (int x = 0; x < BRAILLE_BYTES_POR_FILA; x++) {
            braillePixels[y][x] = 0;
        }
    }
}

// Encender un píxel en el canvas Braille (coordenadas en píxeles)
inline void setPixelBraille(int x, int y) {
    if (x < 0 || x >= BRAILLE_PIXEL_W) return;
    if (y < 0 || y >= BRAILLE_PIXEL_H) return;
    
    int byteIndex = x / 8;
    int bitIndex  = x % 8;
    
    braillePixels[y][byteIndex] |= (1 << bitIndex);
}

// Apagar un píxel en el canvas Braille
inline void clearPixelBraille(int x, int y) {
    if (x < 0 || x >= BRAILLE_PIXEL_W) return;
    if (y < 0 || y >= BRAILLE_PIXEL_H) return;
    
    int byteIndex = x / 8;
    int bitIndex  = x % 8;
    
    braillePixels[y][byteIndex] &= ~(1 << bitIndex);
}

// Consultar si un píxel está encendido
inline bool getPixelBraille(int x, int y) {
    if (x < 0 || x >= BRAILLE_PIXEL_W) return false;
    if (y < 0 || y >= BRAILLE_PIXEL_H) return false;
    
    int byteIndex = x / 8;
    int bitIndex  = x % 8;
    
    return (braillePixels[y][byteIndex] & (1 << bitIndex)) != 0;
}

// Dibujar una línea usando algoritmo de Bresenham
inline void lineaBraille(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    
    while (true) {
        setPixelBraille(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
    }
}

// ============================================================
//  CONVERSIÓN A BRAILLE (PASO 2.1)
// ============================================================

// Convertir un bloque de 2×4 píxeles a un carácter Braille
inline wchar_t convertirBloqueABraille(const bool pixeles[4][2]) {
    int bits = 0;
    
    if (pixeles[0][0]) bits |= (1 << 0);
    if (pixeles[1][0]) bits |= (1 << 1);
    if (pixeles[2][0]) bits |= (1 << 2);
    if (pixeles[0][1]) bits |= (1 << 3);
    if (pixeles[1][1]) bits |= (1 << 4);
    if (pixeles[2][1]) bits |= (1 << 5);
    if (pixeles[3][0]) bits |= (1 << 6);
    if (pixeles[3][1]) bits |= (1 << 7);
    
    return 0x2800 + bits;
}
// ============================================================
//  IMPRIMIR CANVAS BRAILLE (PASO 2.2)
// ============================================================

inline void imprimirBraille(int filaInicio, int colInicio, int color = Color::VERDE_MATRIX) {
    for (int bloqueY = 0; bloqueY < BRAILLE_CHAR_H; bloqueY++) {
        std::cout << "\033[" << (filaInicio + bloqueY) << ";" << colInicio << "H";
        
        for (int bloqueX = 0; bloqueX < BRAILLE_CHAR_W; bloqueX++) {
            bool pixeles[4][2] = {{false}};
            
            for (int py = 0; py < 4; py++) {
                for (int px = 0; px < 2; px++) {
                    int pixelX = bloqueX * 2 + px;
                    int pixelY = bloqueY * 4 + py;
                    if (pixelX < BRAILLE_PIXEL_W && pixelY < BRAILLE_PIXEL_H) {
                        pixeles[py][px] = getPixelBraille(pixelX, pixelY);
                    }
                }
            }
            
            wchar_t brailleChar = convertirBloqueABraille(pixeles);
            char utf8[8] = {0};
            wctomb(utf8, brailleChar);
            std::cout << ansi(color) << utf8 << ansiReset();
        }
    }
    std::cout.flush();
}

// ============================================================
//  DIBUJAR CARÁCTER BRAILLE INDIVIDUAL
//  Dibuja un solo carácter Braille en cualquier posición de la terminal
//  filaTerminal, colTerminal: posición en la terminal
//  puntos: array de 8 bool (true = punto encendido, false = apagado)
//  color: color del carácter (ej. Color::AMARILLO)
// ============================================================

inline void dibujarCaracterBraille(int filaTerminal, int colTerminal, const bool puntos[8], int color) {
    int bits = 0;
    if (puntos[0]) bits |= (1 << 0);
    if (puntos[1]) bits |= (1 << 1);
    if (puntos[2]) bits |= (1 << 2);
    if (puntos[3]) bits |= (1 << 3);
    if (puntos[4]) bits |= (1 << 4);
    if (puntos[5]) bits |= (1 << 5);
    if (puntos[6]) bits |= (1 << 6);
    if (puntos[7]) bits |= (1 << 7);
    
    wchar_t brailleChar = 0x2800 + bits;
    char utf8[8] = {0};
    wctomb(utf8, brailleChar);
    escribirEnPosicion(colTerminal, filaTerminal, std::string(utf8), color);
}