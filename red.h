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
    while (true) {
        char tecla = getchar();
        if (tecla == '\n' || tecla == '\r') continue;
        if (tecla == '1' || tecla == '0' ||
            tecla == 'A' || tecla == 'a') {
            int s = estado.socket.load();
            if (s != -1) {
                char cmd = (tecla == 'a') ? 'A' : tecla;
                // Guardar ultima tecla y redibujar prompt
                stats.ultimaTecla = cmd;
                send(s, &cmd, 1, 0);
                std::lock_guard<std::mutex> lock(estado.mutexDibujo);
                mostrarEstadisticasYPrompt();
            }
        }
    }
}