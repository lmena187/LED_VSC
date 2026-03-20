// ============================================================
//  red.h — TCP con ESP32 y control por teclado
// ============================================================
#pragma once

#include "config.h"
#include "escena.h"
#include "estadisticas.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <cstdio>

inline std::string obtenerIPPuente() {
    FILE* pipe = popen("ip route show | grep default | awk '{print $3}'", "r");
    if (!pipe) return "172.24.0.1";
    char buffer[64]; std::string resultado;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) resultado += buffer;
    pclose(pipe);
    if (!resultado.empty() && resultado.back()=='\n') resultado.pop_back();
    return resultado.empty() ? "172.24.0.1" : resultado;
}

inline void hiloTCP(const std::string& ip, int puerto) {
    while (true) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) { sleep(2); continue; }

        struct sockaddr_in servidor;
        servidor.sin_family = AF_INET;
        servidor.sin_port   = htons(puerto);
        inet_pton(AF_INET, ip.c_str(), &servidor.sin_addr);

        if (connect(sock, (struct sockaddr*)&servidor, sizeof(servidor)) < 0) {
            close(sock); sleep(2); continue;
        }

        estado.socket.store(sock);

        char buffer[256]; std::string lineaActual;
        while (true) {
            int n = recv(sock, buffer, sizeof(buffer)-1, 0);
            if (n <= 0) break;
            buffer[n] = '\0';
            for (int i = 0; i < n; i++) {
                char c = buffer[i];
                if (c == '\r') continue;
                if (c == '\n') {
                    if (lineaActual.find("ESTADO:") != std::string::npos) {
                        try {
                            int val = std::stoi(lineaActual.substr(7));
                            estado.led.store(val);
                            registrarEvento(val);
                            std::lock_guard<std::mutex> lock(estado.mutexDibujo);
                            construirYDibujar();
                        } catch (...) {}
                    }
                    lineaActual.clear();
                } else {
                    lineaActual += c;
                }
            }
        }
        estado.socket.store(-1);
        close(sock);
        sleep(2);
    }
}

inline void hiloTeclado() {
    char teclaEsperando = ' ';

    while (true) {
        char tecla = getchar();

        // Enter — ejecutar la orden en espera
        if (tecla == '\n' || tecla == '\r') {
            if (teclaEsperando == ' ') continue;

            int s = estado.socket.load();
            char cmd = teclaEsperando;
            teclaEsperando = ' ';

            if (cmd == 'M' || cmd == 'm') {
                modoManualActivo = true;
                stats.ultimaTecla = 'M';
                std::lock_guard<std::mutex> lock(estado.mutexDibujo);
                construirYDibujar();

            } else if (cmd == 'A' || cmd == 'a') {
                modoManualActivo = false;
                stats.ultimaTecla = 'A';
                if (s != -1) {
                    char c = 'A';
                    send(s, &c, 1, 0);
                }
                std::lock_guard<std::mutex> lock(estado.mutexDibujo);
                construirYDibujar();

            } else if (cmd == '1' || cmd == '0') {
                if (!modoManualActivo) {
                    // Mostrar mensaje de error debajo del prompt
                    int fila = cfg.filaInicio + H + 8;
                    escribirEnPosicion(2, fila,
                        "  ! TECLA NO VALIDA — ingresa M primero   ",
                        Color::ROJO);
                    std::cout.flush();
                } else {
                    if (s != -1) {
                        stats.ultimaTecla = cmd;
                        send(s, &cmd, 1, 0);
                        std::lock_guard<std::mutex> lock(estado.mutexDibujo);
                        mostrarEstadisticasYPrompt();
                    }
                }
            }
            continue;
        }

        // Tecla valida — mostrar en prompt inmediatamente sin ejecutar
        if (tecla == 'M' || tecla == 'm' ||
            tecla == 'A' || tecla == 'a' ||
            tecla == '1' || tecla == '0') {

            // Limpiar mensaje de error anterior
            int fila = cfg.filaInicio + H + 8;
            limpiarPosicion(2, fila, 50);

            teclaEsperando = tecla;
            stats.ultimaTecla = tecla;
            std::lock_guard<std::mutex> lock(estado.mutexDibujo);
            mostrarEstadisticasYPrompt();
        }
    }
}