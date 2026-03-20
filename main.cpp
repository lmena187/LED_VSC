// ============================================================
//  main.cpp — Arranque del programa
//  Compilar: g++ -std=c++11 main.cpp -o buzzer -pthread
// ============================================================

#include "red.h"
#include <clocale>
#include <thread>
#include <unistd.h>

Config        cfg;
Estado        estado;
Pincel        pincel;
Estadisticas  stats;

std::array<char, 4> canvas[H][W];
int                 canvasColor[H][W];

std::vector<EmojiTag> tags;
std::vector<EmojiTag> tagsDinamicos;

int main() {
    setlocale(LC_ALL, "");

    // Limpiar pantalla
    std::cout << "\033[2J\033[H";
    std::cout.flush();

    // Ocultar lo que escribe el usuario — evita que los numeros
    // aparezcan en lugares incorrectos de la pantalla
    system("stty -echo");

    // EmojiTags fijos
    //tags.push_back({5, 7, "❶", Color::BLANCO_ROTO, false, Color::NEGRO});
    //tags.push_back({4, 8, "OFF", Color::BLANCO_ROTO, false, Color::BLANCO});

    // Hilo TCP
    std::string winIP = obtenerIPPuente();
    std::thread tcp(hiloTCP, winIP, 4000);
    tcp.detach();

    // Hilo Teclado
    std::thread teclado(hiloTeclado);
    teclado.detach();

    std::cout << "\033[" << (3 + H + 1) << ";1H";
    std::cout << "\033[?25h";
    std::cout.flush();

    while (true) { sleep(1); }

    // Restaurar echo al salir (por si acaso)
    system("stty echo");
    return 0;
}