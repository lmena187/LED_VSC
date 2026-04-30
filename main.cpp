// ============================================================
//  main.cpp — Arranque del programa
//  Compilar: g++ -std=c++11 main.cpp -o led -pthread
// ============================================================

#include "red.h"
#include "splash.h"
#include <clocale>
#include <thread>
#include <unistd.h>

// Logo: desactivado hasta tener chafa instalado y ruta confirmada
// Para activar: descomentar el system() y cambiar USAR_LOGO a 1
#define USAR_LOGO 0

Config        cfg;
Estado        estado;
Pincel        pincel;
Estadisticas  stats;
bool          modoManualActivo = false;

std::array<char, 4> canvas[H][W];
int                 canvasColor[H][W];

std::vector<EmojiTag> tags;
std::vector<EmojiTag> tagsDinamicos;

int main() {
    setlocale(LC_ALL, "");

    // Limpiar pantalla
    std::cout << "\033[2J\033[H";
    std::cout.flush();

    // Ocultar lo que escribe el usuario y enviar cada tecla inmediatamente
    system("stty -echo -icanon min 1");
        if (!splashAutenticar()) return 0;
std::cout << "\033[2J\033[H";  // limpiar pantalla antes de arrancar
std::cout.flush();

    // ============================================================
    //  LOGO (activar cuando chafa este instalado y ruta confirmada)
    // ============================================================
#if USAR_LOGO == 1
    system("tput cup 0 4 && chafa -f sixel --size=30x20 '/mnt/c/Users/Usuario/Documents/PlatformIO/Projects/LED_VSC/LOGO/favorita0.png' 2>/dev/null");
#endif

    // Cursor a posicion segura — siempre necesario
    std::cout << "\033[0;0H";
    std::cout.flush();

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

    system("stty echo icanon");
    return 0;
}