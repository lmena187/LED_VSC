// ============================================================
//  main.cpp — Arranque del programa
//  Compilar: g++ -std=c++11 main.cpp -o led -pthread
// ============================================================
#include <signal.h>
#include "red.h"
#include "splash.h"
#include <clocale>
#include <thread>
#include <unistd.h>


#define USAR_LOGO 0

Config        cfg;
Estado        estado;
Pincel        pincel;
Estadisticas  stats;
bool          modoManualActivo = true;

std::array<char, 4> canvas[H][W];
int                 canvasColor[H][W];

std::vector<EmojiTag> tags;
std::vector<EmojiTag> tagsDinamicos;


void manejarSalida(int) {
    system("stty sane");
    std::cout << "\033[38;1H\n";
    std::cout << "\033[?25h";
    std::cout.flush();
    _exit(0);  // termina inmediatamente
}



int main() {
    setlocale(LC_ALL, "");

    signal(SIGINT,  manejarSalida);
    signal(SIGTERM, manejarSalida);

    std::cout << "\033[2J\033[H";
    std::cout.flush();

    system("stty -echo -icanon min 1");

    if (!splashAutenticar()) return 0;

    std::cout << "\033[2J\033[H";
    std::cout.flush();

    construirYDibujar();  // canvas aparece inmediatamente

#if USAR_LOGO == 1
    system("tput cup 0 4 && chafa -f sixel --size=30x20 '/mnt/c/Users/Usuario/Documents/PlatformIO/Projects/LED_VSC/LOGO/favorita0.png' 2>/dev/null");
#endif

    // Hilo TCP
    std::string winIP = obtenerIPPuente();
    std::thread tcp(hiloTCP, winIP, 4000);
    tcp.detach();

    // Hilo Teclado
    std::thread teclado(hiloTeclado);
    teclado.detach();

    std::cout << "\033[?25h";  // mostrar cursor
    std::cout.flush();

    while (true) { sleep(1); }

    system("stty echo icanon");
    return 0;
}