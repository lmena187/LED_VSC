// ============================================================
//  main.cpp — Arranque del programa
//  Compilar: g++ -std=c++11 main.cpp -o led -pthread
// ============================================================

#include "red.h"
#include <clocale>
#include <thread>
#include <unistd.h>

// Opción: activar/desactivar el logo fácilmente
#define USAR_LOGO 1

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

    // ============================================================
    // LOGO MARCA DE AGUA (esquina superior izquierda, fuera del canvas)
    // ============================================================
#if USAR_LOGO == 1
     system("tput cup 0 0 && chafa -f sixel --size=30x20 '/mnt/c/Users/Usuario/Documents/PlatformIO/Projects/LED_VSC/LOGO/favorita.png' 2>/dev/null");
    //system("tput cup 0 0 && chafa -f sixel --size=30x20 '/mnt/c/Users/Usuario/Documents/PlatformIO/Projects/LED_VSC/LOGO/logoCompletoFavorita.png' 2>/dev/null");
    //system("tput cup 0 0 && chafa -f sixel --size=30x15 --brightness 0 --contrast 1.1 '/mnt/c/Users/Usuario/Documents/PlatformIO/Projects/LED_VSC/LOGO/logoCompletoFavorita.png' 2>/dev/null");
   //system("tput cup 0 0 && convert '/mnt/c/Users/Usuario/Documents/PlatformIO/Projects/LED_VSC/LOGO/logoCompletoFavorita.png' -brightness-contrast 40x30 png:- | chafa -f sixel --size=30x20 2>/dev/null");
   //system("tput cup 0 0 && convert '/mnt/c/Users/Usuario/Documents/PlatformIO/Projects/LED_VSC/LOGO/favorita.png' -brightness-contrast 40x30 png:- | chafa -f sixel --size=30x20 2>/dev/null");
    
   // Opcional: devolver el cursor a una posición segura (no afecta al programa)
    std::cout << "\033[0;0H";
    std::cout.flush();
#endif

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