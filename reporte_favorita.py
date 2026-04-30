#!/usr/bin/env python3
# reporte_favorita.py
# Reporte del Sistema de Iluminacion ESP32
# Papel: Formularios continuos PAPELESA 25cm x 27.5cm

from reportlab.pdfgen import canvas
from reportlab.lib.units import cm
from reportlab.lib import colors
from reportlab.lib.utils import ImageReader
from datetime import datetime
import os
import shutil

# ─── CONFIGURACION ────────────────────────────────────────────────────────────
LOGO_PATH   = "/mnt/c/Users/Usuario/Documents/PlatformIO/Projects/LED_VSC/LOGO/favorita0.png"
OUTPUT_PDF  = "/home/luislinux/LED_VSC/reporte_favorita.pdf"
WINDOWS_PDF = "/mnt/c/Users/Usuario/Documents/reporte_favorita.pdf"
STATS_PATH  = "/home/luislinux/LED_VSC/estadisticas.txt"

# Medidas del papel PAPELESA (formulario continuo)
PAGE_W = 25 * cm
PAGE_H = 27.5 * cm

# Medidas y posicion del logo
LOGO_W = 3 * cm
LOGO_H = 2 * cm
LOGO_X = 1.0 * cm
LOGO_Y = PAGE_H - 0.1 * cm - LOGO_H

# Margenes
MARGEN_IZQ = 1.0 * cm
MARGEN_DER = PAGE_W - 1.0 * cm

# Fecha y hora actual
FECHA = datetime.now().strftime("%d/%m/%Y")
HORA  = datetime.now().strftime("%H:%M:%S")

# ─── LEER ESTADISTICAS REALES DEL LED ─────────────────────────────────────────
def leerEstadisticas(path):
    datos = {
        "veces_encendido":    "N/D",
        "segundos_encendido": "N/D",
        "ultimo_evento":      "N/D",
    }
    if not os.path.exists(path):
        return datos
    try:
        with open(path, "r") as f:
            for linea in f:
                linea = linea.strip()
                if "=" in linea:
                    clave, valor = linea.split("=", 1)
                    if clave in datos:
                        datos[clave] = valor
    except Exception:
        pass
    return datos

def formatearSegundos(s):
    try:
        s = int(s)
        h  = s // 3600
        m  = (s % 3600) // 60
        sg = s % 60
        return f"{h:02d}:{m:02d}:{sg:02d}"
    except Exception:
        return str(s)

stats_led = leerEstadisticas(STATS_PATH)

# ─── FUNCIONES AUXILIARES ─────────────────────────────────────────────────────
def linea_simple(c, y):
    c.setStrokeColor(colors.black)
    c.setLineWidth(0.5)
    c.line(MARGEN_IZQ, y, MARGEN_DER, y)

def linea_doble(c, y):
    c.setStrokeColor(colors.black)
    c.setLineWidth(1.0)
    c.line(MARGEN_IZQ, y,     MARGEN_DER, y)
    c.line(MARGEN_IZQ, y - 2, MARGEN_DER, y - 2)

def titulo_seccion(c, texto, y, size=8):
    c.setFont("Helvetica-Bold", size)
    c.setFillColor(colors.black)
    c.drawString(MARGEN_IZQ, y, texto.upper())

def fila_texto(c, etiqueta, valor, y, bold=False):
    fuente = "Helvetica-Bold" if bold else "Helvetica"
    c.setFont(fuente, 7.5)
    c.setFillColor(colors.black)
    puntos = "." * max(1, 42 - len(etiqueta))
    c.drawString(MARGEN_IZQ + 0.3*cm, y, etiqueta + puntos)
    c.drawRightString(MARGEN_DER, y, valor)

def texto_centro(c, texto, y, size=7.5, bold=False):
    fuente = "Helvetica-Bold" if bold else "Helvetica"
    c.setFont(fuente, size)
    c.drawCentredString(PAGE_W / 2, y, texto)

# ─── GENERACION DEL PDF ───────────────────────────────────────────────────────
c = canvas.Canvas(OUTPUT_PDF, pagesize=(PAGE_W, PAGE_H))

y = PAGE_H - 0.5*cm

# ── LOGO ──────────────────────────────────────────────────────────────────────
if os.path.exists(LOGO_PATH):
    img = ImageReader(LOGO_PATH)
    c.drawImage(img, LOGO_X, LOGO_Y,
                width=LOGO_W, height=LOGO_H,
                mask='auto', preserveAspectRatio=True)
else:
    c.setFont("Helvetica-Bold", 9)
    c.drawString(LOGO_X, LOGO_Y + 0.3*cm, "[LOGO NO ENCONTRADO]")

# ── ENCABEZADO ────────────────────────────────────────────────────────────────
y = PAGE_H - 0.7*cm
c.setFont("Helvetica-Bold", 9)
c.drawRightString(MARGEN_DER, y, "SISTEMA DE ILUMINACION ESP32")
y -= 0.4*cm
c.setFont("Helvetica", 7)
c.drawRightString(MARGEN_DER, y, "Casa de Luis Mena")
y -= 0.35*cm
c.drawRightString(MARGEN_DER, y, "Santo Domingo de los Tsachilas, Ecuador")
y -= 0.35*cm
c.drawRightString(MARGEN_DER, y, f"Fecha: {FECHA}   Hora: {HORA}")

y -= 0.3*cm
linea_doble(c, y)
y -= 0.4*cm

# ── TITULO ────────────────────────────────────────────────────────────────────
texto_centro(c, "REPORTE DE ESTADISTICAS — LED RGB", y, size=9, bold=True)
y -= 0.5*cm
linea_simple(c, y)
y -= 0.4*cm

# ── ESTADISTICAS ESP32 ────────────────────────────────────────────────────────
titulo_seccion(c, "Estadisticas del Sistema", y)
y -= 0.5*cm
fila_texto(c, "Veces encendido",
    stats_led["veces_encendido"], y)
y -= 0.45*cm
fila_texto(c, "Tiempo total encendido",
    formatearSegundos(stats_led["segundos_encendido"]), y)
y -= 0.45*cm
fila_texto(c, "Ultimo evento",
    stats_led["ultimo_evento"], y)
y -= 0.45*cm

y -= 0.2*cm
linea_doble(c, y)
y -= 0.5*cm

# ── PIE DE PAGINA ─────────────────────────────────────────────────────────────
texto_centro(c, "*** FIN DEL REPORTE ***", y, size=7.5, bold=True)
y -= 0.4*cm
texto_centro(c, "Generado desde: Ubuntu 24.04 LTS", y, size=6.5)
y -= 0.3*cm
texto_centro(c, "Herramientas: Python 3 + ReportLab 4.4  |  Costo de licencias: $0.00", y, size=6.5)
y -= 0.3*cm
texto_centro(c, "Impresion: Epson FX-890II  |  Papel: Formulario Continuo PAPELESA 25x27.5cm", y, size=6.5)

# ─── GUARDAR Y COPIAR A WINDOWS ───────────────────────────────────────────────
c.save()
shutil.copy2(OUTPUT_PDF, WINDOWS_PDF)
