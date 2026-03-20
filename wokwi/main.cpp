#include <Arduino.h>

#define LED_PIN 16

bool modoManual = false;
int estadoManual = 0;
int estadoAnterior = -1;  // para detectar cambios

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Escuchar comandos entrantes
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == '1') {
      modoManual = true;
      estadoManual = 1;
    } else if (cmd == '0') {
      modoManual = true;
      estadoManual = 0;
    } else if (cmd == 'A') {
      modoManual = false;
      estadoAnterior = -1;  // resetear para que automatico funcione normal
    }
  }

  if (modoManual) {
    digitalWrite(LED_PIN, estadoManual);
    // Solo enviar si el estado cambio
    if (estadoManual != estadoAnterior) {
      Serial.println(estadoManual == 1 ? "ESTADO:1" : "ESTADO:0");
      estadoAnterior = estadoManual;
    }
    delay(100);  // delay corto solo para no saturar el procesador
  } else {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("ESTADO:1");
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    Serial.println("ESTADO:0");
    delay(1000);
  }
}