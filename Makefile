# ============================================================
#  Makefile
#  Proyecto: Sistema de Luces con ESP32
#  Uso:
#    make        → compilar
#    make run    → compilar y ejecutar
#    make clean  → borrar ejecutable
#    make help   → mostrar comandos disponibles
# ============================================================

# ── Compilador y flags ──────────────────────────────────────
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread

# ── Archivos del proyecto ───────────────────────────────────
TARGET  = led
MAIN    = main.cpp
HEADERS = config.h canvas.h escena.h red.h estadisticas.h braille.h

# ── Colores para mensajes en terminal ───────────────────────
VERDE   = \033[0;32m
AMARILLO= \033[0;33m
AZUL    = \033[0;34m
RESET   = \033[0m

# ============================================================
#  COMPILAR (target por defecto)
# ============================================================
all: $(TARGET)

$(TARGET): $(MAIN) $(HEADERS)
	@echo "$(AZUL)[ Compilando ]$(RESET) Sistema de Luces ESP32..."
	@$(CXX) $(CXXFLAGS) $(MAIN) -o $(TARGET)
	@echo "$(VERDE)[ OK         ]$(RESET) $(TARGET) generado correctamente"

# ============================================================
#  COMPILAR Y EJECUTAR
# ============================================================
run: $(TARGET)
	@echo "$(AMARILLO)[ Ejecutando ]$(RESET) ./$(TARGET)"
	@./$(TARGET)

# ============================================================
#  LIMPIAR EJECUTABLE
# ============================================================
clean:
	@echo "$(AMARILLO)[ Limpiando  ]$(RESET) Eliminando ejecutable..."
	@rm -f $(TARGET)
	@echo "$(VERDE)[ OK         ]$(RESET) Listo"

# ============================================================
#  AYUDA
# ============================================================
help:
	@echo ""
	@echo "$(AZUL)  Sistema de Luces ESP32 — Comandos disponibles:$(RESET)"
	@echo ""
	@echo "  $(VERDE)make$(RESET)        → Compilar el proyecto"
	@echo "  $(VERDE)make run$(RESET)    → Compilar y ejecutar"
	@echo "  $(VERDE)make clean$(RESET)  → Eliminar ejecutable"
	@echo "  $(VERDE)make help$(RESET)   → Mostrar esta ayuda"
	@echo ""

# Evitar conflictos con archivos del mismo nombre
.PHONY: all run clean help
