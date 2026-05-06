// ============================================================
//  splash.h — Pantalla de bienvenida con logo Braille
//  Para cambiar tamano: regenerar logo en a.tools/image-to-braille
//  Para cambiar clave:  modificar SPLASH_CLAVE
//  Para cambiar color:  modificar SPLASH_COLOR
//  Para cambiar posicion: modificar SPLASH_FILA y SPLASH_MARGEN
// ============================================================
#pragma once

#include "config.h"
#include "canvas.h"
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

// ── CONFIGURACION (editar aqui) ──────────────────────────
static const char*  SPLASH_CLAVE        = "1234";
static const int    SPLASH_COLOR        = Color::VERDE_MATRIX;
static const int    SPLASH_MARGEN       = 12;    // columnas desde la izquierda
static const int    SPLASH_FILA         = 0;     // fila donde empieza el logo
static const int    SPLASH_MAX_INTENTOS = 3;     // intentos antes de bloquear
static const int    SPLASH_ANCHO_TERM   = 125;   // ancho de la terminal
static const int    SPLASH_ANCHO_CAMPO  = 20;    // ancho del campo de clave

// ── LOGO BRAILLE (logo + texto FAVORITA) ─────────────────
static const int SPLASH_FILAS = 26;

static const char* SPLASH_LOGO[] = {
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣶⣾⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠉⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⠋⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠀⠀⢀⢀⣠⣴⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⠟⠋⠀⠀⢀⣠⣴⣷⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⢀⡔⠒⠄⠀⢠⡔⠒⢦⠀⠀⠰⡖⢢⡄⠀⠀⣶⠰⣄⠀⠀⡤⠒⢰⡀⠀⠀⣖⠢⣆⠀⠀⠀⣰⠀⠀⠀⢠⠔⠒⡀⠀⢲⠄⠀⠀⡔⠐⢢⡀⠀⠐⣴⡀⢰⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⠟⠉⠀⠀⣀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⡃⠀⠀⠀⠀⠀⠀⢺⠄⠀⠀⠀⣺⡂⠀⢸⠇⠀⠨⡧⣞⠁⠀⠀⣯⠤⠏⠀⢸⡇⠀⢐⡗⠀⠀⡿⢴⡃⠀⠀⢰⣹⡂⠀⠀⣿⠀⠀⠀⠀⢺⠅⠀⢸⡇⠀⢘⡗⠀⠠⡉⢷⣸⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⡿⠋⠀⠀⣠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠁⠀⠀⠀⠀⠀⠀⠘⠧⠤⠄⠀⠘⠧⠠⠞⠁⠀⠨⠧⠙⠦⠀⠀⠯⠄⠀⠀⠀⠫⠤⠔⠃⠀⠀⠿⠈⠷⠀⠠⠅⠀⠿⠀⠀⠙⠦⠤⠀⠀⠺⠅⠀⠀⠳⠄⠜⠁⠀⠰⠄⠀⠻⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⢠⣿⣿⣿⡿⠋⠀⢀⣴⣽⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⢠⣿⣿⡿⠋⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣀⣠⣀⣠⣀⣀⠀⠀⠀⢠⡀⠀⠀⣀⣠⣀⣠⠀⠀⢀⣄⣀⡀⠀⢀⣠⡤⣤⣄⣀⠀⠀⠀⣀⣄⣠⣠⣠⣀⡀⠀⠀⠀⣠⣀⣠⣀⢀⣄⣠⣀⣄⣠⣀⣄⡄⠀⠀⠀⣠⡀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⢀⣿⣿⠟⠀⠀⣴⣿⣿⣿⣿⣿⣿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠈⠇⠀⠀⢠⣿⣷⠀⠀⠀⢹⣿⣆⠀⠀⢀⡾⠁⢀⣼⡟⠁⠀⠀⠈⢻⣷⡄⠀⠀⢼⣿⡂⠀⠹⣿⣧⠀⠀⠐⣿⣯⠀⠨⡇⠀⢨⣿⡗⠀⠨⠇⠀⠀⢠⣿⣧⠀⠀⠀⠀⠀",
    "⠀⠀⠀⣼⣿⠃⠀⢠⣾⣿⣿⣿⣿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣀⢀⡤⠀⠀⢀⡞⠹⣿⣆⠀⠀⠀⢿⣷⠄⠀⣼⠁⠀⣺⣿⡇⠀⠀⠀⠀⢘⣿⣿⠀⠀⢺⣿⡂⣀⣸⡿⠃⠀⠀⢈⣿⣗⠀⠀⠀⠀⢐⣿⣏⠀⠀⠀⠀⢠⡏⢹⣿⡆⠀⠀⠀⠀",
    "⠀⠀⠀⣿⠁⠀⣰⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠉⠉⠇⠀⠀⡾⠥⠤⢿⣿⡄⠀⠀⠘⣿⣧⢰⠃⠀⠀⣻⣿⡇⠀⠀⠀⠀⢐⣿⡿⠀⠀⢺⣿⡋⢻⣿⣄⠀⠀⠀⠐⣿⡯⠀⠀⠀⠀⢐⣿⡧⠀⠀⠀⢀⡾⠤⠤⣿⣿⡀⠀⠀⠀",
    "⠀⠀⢸⠃⠀⣴⣿⣿⣿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⣼⠃⠀⠀⠨⣿⣷⠀⠀⠀⠸⣿⡏⠀⠀⠀⠈⢿⣷⡀⠀⠀⢀⣼⡿⠁⠀⠀⢺⣿⠆⠀⠻⣿⣦⠀⠀⠨⣿⣟⠀⠀⠀⠀⠰⣿⡗⠀⠀⠀⣼⠁⠀⠀⠨⣿⣷⠀⠀⠀",
    "⠀⠀⠈⠀⣸⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠊⠋⠋⠓⠀⠀⠋⠋⠃⠀⠀⠒⠋⠋⠛⠀⠀⠀⠋⠀⠀⠀⠀⠀⠀⠉⠛⠓⠚⠙⠁⠀⠀⠀⠘⠋⠛⠓⠀⠀⠉⠛⠓⠂⠋⠛⠙⠒⠀⠀⠐⠛⠙⠋⠓⠀⠋⠛⠂⠀⠀⠊⠋⠋⠓⠂⠀",
    "⠀⠀⠀⢠⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⣾⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠠⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠸⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
};

// ── FUNCIONES ────────────────────────────────────────────

inline void splashMostrarLogo() {
    std::cout << "\033[2J\033[H";
    std::cout.flush();
    for (int i = 0; i < SPLASH_FILAS; i++) {
        std::cout << "\033[" << (SPLASH_FILA + i) << ";" << SPLASH_MARGEN << "H";
        std::cout << ansi(SPLASH_COLOR) << SPLASH_LOGO[i] << ansiReset();
    }
    std::cout.flush();
}

// Leer clave manteniendo el fondo verde del campo
inline std::string splashLeerClave(int filaClave, int colCampo) {
    struct termios old, nuevo;
    tcgetattr(STDIN_FILENO, &old);
    nuevo = old;
    nuevo.c_lflag &= ~(ECHO | ICANON);
    nuevo.c_cc[VMIN]  = 1;
    nuevo.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &nuevo);

    std::string clave;
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == '\n' || c == '\r') break;
        if (c == 127 || c == '\b') {
            if (!clave.empty()) {
                clave.pop_back();
            }
        } else {
            if ((int)clave.length() < SPLASH_ANCHO_CAMPO) {
                clave += c;
            }
        }
        // Redibujar campo completo con fondo verde
        std::cout << "\033[" << filaClave << ";" << colCampo << "H";
        std::cout << ansiFondo256(Color::VERDE_CLARO);  //////////////////////////////////////
        std::string asteriscos((int)clave.length(), '*');
        std::string espacios(SPLASH_ANCHO_CAMPO - (int)clave.length(), ' ');
        std::cout << ansi(Color::BLANCO_INTENSO) << asteriscos << espacios << "\033[0m";
        // Cursor al final de los asteriscos
        std::cout << "\033[" << filaClave << ";" << (colCampo + (int)clave.length()) << "H";
        std::cout.flush();
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return clave;
}

inline bool splashAutenticar() {
    splashMostrarLogo();

    // Calcular filas
    int filaFranja     = SPLASH_FILA + SPLASH_FILAS;
    int filaDecorativa = filaFranja + 1;
    int filaClave      = filaDecorativa + 2;
    int filaMensaje    = filaClave + 1;
    //int filaTeclas     = filaMensaje + 2;
    int filaInstruccion = filaMensaje + 1;
    int filaTeclas      = filaInstruccion + 5;

    // Franja descriptiva — fondo verde matrix, texto blanco
    std::string franja = "   SISTEMA OPERATIVO LINUX   |   Ubuntu 24.04 LTS   ";
    int colFranja = (SPLASH_ANCHO_TERM - (int)franja.length()) / 2;
    escribirEnPosicionConFondo(colFranja, filaFranja, franja, Color::BLANCO, Color::VERDE_CLARO, true);/////////

    // Linea decorativa
    std::string decoracion = "──────────────────────────────────────────────────";
    int longitudReal = 50;
    int colDecoracion = (SPLASH_ANCHO_TERM - longitudReal) / 2;
    escribirEnPosicion(colDecoracion, filaDecorativa, decoracion, SPLASH_COLOR);

    // Teclas de funcion — solo texto, estilo wireframe
    std::string teclas = "  F1        F2        F3        F4        F5        F6  ";
    int colTeclas = (SPLASH_ANCHO_TERM - (int)teclas.length()) / 2;
    // Instruccion al usuario
std::string instruccion = "Digite ENTER luego de ingresar su codigo";
int colInstruccion = (SPLASH_ANCHO_TERM - (int)instruccion.length()) / 2;
escribirEnPosicion(colInstruccion, filaInstruccion, instruccion, SPLASH_COLOR);
    escribirEnPosicion(colTeclas, filaTeclas, teclas, SPLASH_COLOR);
    std::cout.flush();

    // Label y campo de clave
    std::string labelClave = "  Codigo de Operador: ";
    int colClave = (SPLASH_ANCHO_TERM - (int)labelClave.length() - SPLASH_ANCHO_CAMPO) / 2;
    int colCampo = colClave + (int)labelClave.length();

    int intentos = 0;
    while (intentos < SPLASH_MAX_INTENTOS) {
        limpiarPosicion(1, filaClave,   120);
        limpiarPosicion(1, filaMensaje, 120);

        // Label
        escribirEnPosicion(colClave, filaClave, labelClave, SPLASH_COLOR);

        // Campo con fondo verde inicial
        std::cout << "\033[" << filaClave << ";" << colCampo << "H";
        std::cout << ansiFondo256(Color::VERDE_CLARO); //////////////////////////////////
        std::string campoVacio(SPLASH_ANCHO_CAMPO, ' ');
        std::cout << ansi(Color::BLANCO_INTENSO) << campoVacio << "\033[0m";

        // Cursor al inicio del campo
        std::cout << "\033[" << filaClave << ";" << colCampo << "H";
        std::cout.flush();

        std::string clave = splashLeerClave(filaClave, colCampo);

        if (clave == SPLASH_CLAVE) {
            std::string msgOk = "✓  Acceso concedido";
            int colOk = (SPLASH_ANCHO_TERM - (int)msgOk.length()) / 2;
            escribirEnPosicion(colOk, filaMensaje, msgOk, SPLASH_COLOR, true);
            std::cout.flush();
            sleep(1);
            return true;
        } else {
            intentos++;
            int restantes = SPLASH_MAX_INTENTOS - intentos;
            std::string msgErr;
            if (restantes > 0) {
                msgErr = "✗  Clave incorrecta — intentos restantes: " + std::to_string(restantes);
            } else {
                msgErr = "✗  Acceso bloqueado";
            }
            int colErr = (SPLASH_ANCHO_TERM - (int)msgErr.length()) / 2;
            escribirEnPosicion(colErr, filaMensaje, msgErr, Color::ROJO, true);
            std::cout.flush();
            sleep(2);
        }
    }
    return false;
}