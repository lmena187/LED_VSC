// ============================================================
//  canvas.h — Motor grafico, parser SVG y funciones de texto
// ============================================================
#pragma once

#include "config.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <cctype>
#include <sys/ioctl.h>
#include <unistd.h>

inline std::string ansi(int color) {
    if (!cfg.usarColores || color == Color::RESET) return "";
    std::ostringstream oss;
    if (color >= 30 && color <= 37) oss << "\033[" << color << "m";
    else oss << "\033[38;5;" << color << "m";
    return oss.str();
}

inline std::string ansiFondo256(int color) {
    if (!cfg.usarColores) return "";
    std::ostringstream oss;
    if (color >= 30 && color <= 37) oss << "\033[" << (color + 10) << "m";
    else oss << "\033[48;5;" << color << "m";
    return oss.str();
}

inline std::string ansiReset() {
    if (!cfg.usarColores) return "";
    return "\033[0m";
}

inline void clearCanvas() {
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++) {
            canvas[y][x][0] = ' '; canvas[y][x][1] = '\0';
            canvas[y][x][2] = '\0'; canvas[y][x][3] = '\0';
            canvasColor[y][x] = Color::RESET;
        }
}

inline void setPixel(int x, int y, const char* c) {
    if (x >= 0 && x < W && y >= 0 && y < H) {
        for (int i = 0; i < 4; i++) { canvas[y][x][i] = c[i]; if (c[i] == '\0') break; }
        canvasColor[y][x] = pincel.color;
    }
}

inline void line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2-x1), dy = abs(y2-y1);
    int sx = (x1<x2)?1:-1, sy = (y1<y2)?1:-1, err = dx-dy;
    while (true) {
        for (int gy = -(pincel.grosor/2); gy <= pincel.grosor/2; gy++)
            for (int gx = -(pincel.grosor/2); gx <= pincel.grosor/2; gx++)
                setPixel(x1+gx, y1+gy, pincel.trazo);
        if (x1==x2 && y1==y2) break;
        int e2 = 2*err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
}

  inline std::vector<Punto> parseSVG(const std::string& d, bool ladoIndependiente = false) {
    std::vector<Punto> vertices;
    std::string n = d;
    // Acepta formato Inkscape multilinea y formato de una sola linea
    for (size_t i = 0; i < n.length(); i++) {
        if (n[i]=='\n' || n[i]=='\r' || n[i]=='\t') n[i]=' ';
        if (n[i]==',') n[i]=' ';
    }
    std::istringstream ss(n);
    int curX=0, curY=0; char cmd=' '; bool primerMov=true, relativo=false;
    std::string token;
    while (ss >> token) {
        if (token.length()==1 && isalpha(token[0])) {
            cmd = token[0]; relativo = islower(cmd);
            if (cmd=='Z'||cmd=='z') { if (!vertices.empty()) vertices.push_back(vertices[0]); continue; }
            if (cmd=='H'||cmd=='h'||cmd=='V'||cmd=='v') {
                double v; if (ss>>v) {
                    int vi=(int)round(v);
                    if      (cmd=='H') curX=vi;
                    else if (cmd=='h') curX+=vi;
                    // Correccion de aspecto: V se divide a la mitad
                    // porque las celdas de la terminal son el doble de altas que anchas
                    else if (cmd=='V') curY=(int)round(v/2.0);
                    else               curY+=(int)round(v/2.0);
                    vertices.push_back({curX,curY});
                } continue;
            }
    
                double x,y; if (ss>>x>>y) {
    int xi=(int)round(x);
    // Correccion de aspecto en Y para lados independientes
    int yi = ladoIndependiente ? (int)round(y/2.0) : (int)round(y);
    if (cmd=='M'){curX=xi;curY=yi;primerMov=false;}
    else if (cmd=='m'){if(primerMov){curX=xi;curY=yi;primerMov=false;}else{curX+=xi;curY+=yi;}}
    else if (cmd=='L'){curX=xi;curY=yi;}
    else if (cmd=='l'){curX+=xi;curY+=yi;}
                vertices.push_back({curX,curY});
            }
        } else if (isdigit(token[0])||token[0]=='-'||token[0]=='.') {
            double x=std::stod(token), y; if (ss>>y) {
                int xi=(int)round(x), yi=(int)round(y);
                if (relativo&&!primerMov){curX+=xi;curY+=yi;}
                else{curX=xi;curY=yi;if(cmd=='m'||cmd=='M')primerMov=false;}
                vertices.push_back({curX,curY});
            }
        }
    }
    return vertices;
}

inline void escribirTexto(int x, int y, const std::string& t, int color) {
    pincel.color = color;
    for (size_t i = 0; i < t.length(); i++) { char c[2]={t[i],'\0'}; setPixel(x+i,y,c); }
}

inline void escribirTextoVertical(int x, int y, const std::string& t, int color) {
    pincel.color = color;
    for (size_t i = 0; i < t.length(); i++) { char c[2]={t[i],'\0'}; setPixel(x,y+i,c); }
}

inline void limpiarPosicion(int x, int y, int ancho) {
    std::cout << "\033[" << y << ";" << x << "H" << std::string(ancho,' ');
    std::cout.flush();
}

inline void escribirEnPosicion(int x, int y, const std::string& texto,
                               int color, bool negrita = false) {
    std::cout << "\033[" << y << ";" << x << "H";
    if (negrita) std::cout << "\033[1m";
    std::cout << ansi(color) << texto << ansiReset();
    if (negrita) std::cout << "\033[0m";
}

inline void escribirEnPosicionConFondo(int x, int y, const std::string& texto,
                                       int colorTexto, int colorFondo,
                                       bool negrita = false) {
    std::cout << "\033[" << y << ";" << x << "H";
    if (negrita) std::cout << "\033[1m";
    std::cout << ansi(colorTexto) << ansiFondo256(colorFondo) << texto << "\033[0m";
}

inline void dibujarTags(const std::vector<EmojiTag>& lista) {
    for (const auto& t : lista) {
        if (t.tieneFondo) escribirEnPosicionConFondo(t.x,t.y,t.valor,t.color,t.colorFondo);
        else escribirEnPosicion(t.x,t.y,t.valor,t.color);
    }
}

inline void imprimirCanvas() {
    std::cout << "\033[?25l";
    for (int y = 0; y < H; y++) {
        std::cout << "\033[" << (cfg.filaInicio+y) << ";" << cfg.colInicio << "H"
                  << "\033[2K"
                  << "\033[" << (cfg.filaInicio+y) << ";" << cfg.colInicio << "H";
        for (int x = 0; x < W; x++) {
            const char* c = canvas[y][x].data();
            int col = canvasColor[y][x];
            if (col!=Color::RESET) std::cout << ansi(col) << c << ansiReset();
            else if (cfg.mostrarPuntos) std::cout << ansi(Color::GRIS_CLARO) << '.' << ansiReset();
            else                        std::cout << ' ';
        }
        std::cout << ansiReset();
    }
    std::cout << "\033[?25h";
}