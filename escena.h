// ============================================================
//  escena.h — Diseno visual y orquestacion de capas
//  Para cambiar el diseno visual — editar solo este archivo.
// ============================================================
#pragma once

#include "config.h"
#include "canvas.h"
#include "estadisticas.h"

// ============================================================
//  CONSTRUIR FIGURAS SVG
// ============================================================
inline void construirFiguras() {
    std::vector<Figura> figuras;

// ============================================================
//  CUADRADO CON LADOS INDEPENDIENTES/SEPARADOS Y ESQUINAS
//  Estilo wireframe técnico con caracteres de esquina
// Las esquinas se dibujan por separado "└"
// ============================================================

// ============================================================
//  VEREDA (2 lados independientes)
// ============================================================

// Vereda frente (horizontal)
Figura veredaFrente;
veredaFrente.path   = "M 13,46 H 73";
veredaFrente.color  = Color::VERDE_MATRIX;
veredaFrente.trazo  = "─";
veredaFrente.grosor = 1;
veredaFrente.ladoIndependiente = true;
figuras.push_back(veredaFrente);

// Vereda lateral (vertical)
Figura veredaLateral;
veredaLateral.path   = "M 12,0 V 44";
veredaLateral.color  = Color::VERDE_MATRIX;
veredaLateral.trazo  = "│";
veredaLateral.grosor = 1;
veredaLateral.ladoIndependiente = true;
figuras.push_back(veredaLateral);

// ============================================================
//  CERRAMIENTO DE LA CASA (4 lados independientes)
// ============================================================

// Lado trasero (horizontal)
Figura cerramientoTrasero;
cerramientoTrasero.path   = "M 20,0 H 69";
cerramientoTrasero.color  = Color::VERDE_MATRIX;
cerramientoTrasero.trazo  = "─";
cerramientoTrasero.grosor = 1;
cerramientoTrasero.ladoIndependiente = true;
figuras.push_back(cerramientoTrasero);

// Lado frontal (horizontal)
Figura cerramientoFrontal;
cerramientoFrontal.path   = "M 60,39 H 21";
cerramientoFrontal.color  = Color::VERDE_MATRIX;
cerramientoFrontal.trazo  = "─";
cerramientoFrontal.grosor = 1;
cerramientoFrontal.ladoIndependiente = true;
figuras.push_back(cerramientoFrontal);

// Lado derecho (vertical)
Figura cerramientoDerecho;
cerramientoDerecho.path   = "M 70,1 V 38";
cerramientoDerecho.color  = Color::VERDE_MATRIX;
cerramientoDerecho.trazo  = "│";
cerramientoDerecho.grosor = 1;
cerramientoDerecho.ladoIndependiente = true;
figuras.push_back(cerramientoDerecho);

// Lado izquierdo (vertical)
Figura cerramientoIzquierdo;
cerramientoIzquierdo.path   = "M 20,38 V 1";
cerramientoIzquierdo.color  = Color::VERDE_MATRIX;
cerramientoIzquierdo.trazo  = "│";
cerramientoIzquierdo.grosor = 1;
cerramientoIzquierdo.ladoIndependiente = true;
figuras.push_back(cerramientoIzquierdo);
// ============================================================
//  DORMITORIO (5 lados independientes)
// ============================================================

// Lado trasero (horizontal)
Figura dormitorioTrasero;
dormitorioTrasero.path   = R"(M 28,0
                               H 44)";
dormitorioTrasero.color  = Color::VERDE_MATRIX;
dormitorioTrasero.trazo  = "─";
dormitorioTrasero.grosor = 1;
dormitorioTrasero.ladoIndependiente = true;
figuras.push_back(dormitorioTrasero);

// Lado frontal izquierdo (horizontal, relativo)
Figura dormitorioFrontalIzquierdo;
dormitorioFrontalIzquierdo.path   = R"(m 32,12
                                        h -3)";
dormitorioFrontalIzquierdo.color  = Color::VERDE_MATRIX;
dormitorioFrontalIzquierdo.trazo  = "─";
dormitorioFrontalIzquierdo.grosor = 1;
dormitorioFrontalIzquierdo.ladoIndependiente = true;
figuras.push_back(dormitorioFrontalIzquierdo);

// Lado frontal derecho (horizontal)
Figura dormitorioFrontalDerecho;
dormitorioFrontalDerecho.path   = R"(M 37,12
                                      H 42)";
dormitorioFrontalDerecho.color  = Color::VERDE_MATRIX;
dormitorioFrontalDerecho.trazo  = "─";
dormitorioFrontalDerecho.grosor = 1;
dormitorioFrontalDerecho.ladoIndependiente = true;
figuras.push_back(dormitorioFrontalDerecho);

// Lado derecho (vertical)
Figura dormitorioDerecho;
dormitorioDerecho.path   = R"(M 42,1
                               V 10)";
dormitorioDerecho.color  = Color::VERDE_MATRIX;
dormitorioDerecho.trazo  = "│";
dormitorioDerecho.grosor = 1;
dormitorioDerecho.ladoIndependiente = true;
figuras.push_back(dormitorioDerecho);

// Lado izquierdo (vertical)
Figura dormitorioIzquierdo;
dormitorioIzquierdo.path   = R"(M 28,10
                                 V 1)";
dormitorioIzquierdo.color  = Color::VERDE_MATRIX;
dormitorioIzquierdo.trazo  = "│";
dormitorioIzquierdo.grosor = 1;
dormitorioIzquierdo.ladoIndependiente = true;
figuras.push_back(dormitorioIzquierdo);

// ============================================================
//  PORTON / PUERTA DE GARAJE (4 lados independientes)
// ============================================================

pincel.color = Color::ROJO;
setPixel(70, 19, "┐");  // superior derecha

// Lado superior
Figura portonSuperior;
portonSuperior.path   = "M 61,38 H 69";
portonSuperior.color  = Color::VERDE_MATRIX;
portonSuperior.trazo  = "─";
portonSuperior.grosor = 1;
portonSuperior.ladoIndependiente = true;
figuras.push_back(portonSuperior);

// Lado inferior
Figura portonInferior;
portonInferior.path   = "M 69,42 H 61";
portonInferior.color  = Color::VERDE_MATRIX;
portonInferior.trazo  = "─";
portonInferior.grosor = 1;
portonInferior.ladoIndependiente = true;
figuras.push_back(portonInferior);

// Lado izquierdo
Figura portonIzquierdo;
portonIzquierdo.path   = "M 60,40 V 40";
portonIzquierdo.color  = Color::VERDE_MATRIX;
portonIzquierdo.trazo  = "│";
portonIzquierdo.grosor = 1;
portonIzquierdo.ladoIndependiente = true;
figuras.push_back(portonIzquierdo);

// Lado derecho
Figura portonDerecho;
portonDerecho.path   = "m 70,40 v 0";
portonDerecho.color  = Color::VERDE_MATRIX;
portonDerecho.trazo  = "│";
portonDerecho.grosor = 1;
portonDerecho.ladoIndependiente = true;
figuras.push_back(portonDerecho);



  for (size_t i = 0; i < figuras.size(); i++) {
        pincel.color  = figuras[i].color;
        pincel.trazo  = figuras[i].trazo;
        pincel.grosor = figuras[i].grosor;
        //std::vector<Punto> verts = parseSVG(figuras[i].path);
        std::vector<Punto> verts = parseSVG(figuras[i].path, figuras[i].ladoIndependiente);
        for (size_t j = 0; j+1 < verts.size(); j++)
            line(verts[j].x, verts[j].y, verts[j+1].x, verts[j+1].y);
    }
}

// ============================================================
//  ACTUALIZAR TAGS DINAMICOS
// ============================================================
inline void actualizarTagsDinamicos() {
    tagsDinamicos.clear();
    if (estado.led.load() == 1) {
        limpiarPosicion(14, 8, 20);
        tagsDinamicos.push_back({57, 9, "❶", Color::AMARILLO});
        tagsDinamicos.push_back({57,10, "ON",  Color::AMARILLO});
    } else {
        limpiarPosicion(14, 8, 20);
        tagsDinamicos.push_back({57, 9, "❶",  Color::BLANCO_ROTO});
        tagsDinamicos.push_back({57, 10, "OFF", Color::BLANCO_ROTO});
        //tagsDinamicos.push_back({57, 10, "ᵒⁿ", Color::AMARILLO});  // superíndice
    
    
     // tagsDinamicos.push_back({50, 2, "𝙎𝙄𝙎𝙏𝙀𝙈𝘼 𝘿𝙀 𝙇𝙐𝘾𝙀𝙎 𝘼𝙐𝙏𝙊𝙈𝘼𝙏𝙄𝘾𝘼𝙎", Color::VERDE_MATRIX});
    
    
    }
}

// ============================================================
//  MOSTRAR ESTADISTICAS Y PROMPT
// ============================================================
inline void mostrarEstadisticasYPrompt() {
    // fila base del bloque de estadisticas
    // para mover todo el bloque cambia cfg.filaStats en config.h
    int fila = cfg.filaInicio + H + cfg.filaStats;

    std::string teclaStr = (stats.ultimaTecla == ' ') ? " " : std::string(1, stats.ultimaTecla);

    // Linea 1 — modo actual y teclas disponibles
    if (modoManualActivo) {
        escribirEnPosicion(2, fila,
            "  Modo: MANUAL     Teclas: 1=ON  0=OFF  A=AUTO        ",
            Color::VERDE_MATRIX, true);
    } else {
        escribirEnPosicion(2, fila,
            "  Modo: AUTOMATICO    Teclas: M=Manual  A=Auto        ",
            Color::VERDE_MATRIX, true);
    }

    // Linea 2 — prompt con ultima tecla presionada
    escribirEnPosicion(2, fila + 1,
        "  > [" + teclaStr + "]                    ",
        Color::VERDE_MATRIX);

    // Cursor al final del prompt
    std::cout << "\033[" << (fila + 1) << ";8H";
    std::cout.flush();
}
// ============================================================
//  CONSTRUIR Y DIBUJAR
// ============================================================
inline void construirYDibujar() {
    clearCanvas();
    construirFiguras();

// ============================================================
//  ESCRIBIR TEXTO ESTATICO USANDO PIXELES Y ESCRIBIR EN POSICIONES FIJAS
// ============================================================

    pincel.color = Color::VERDE_MATRIX;
    
    escribirTexto(33,         25, "CALLE SARAJEVO", Color::VERDE_MATRIX);
     setPixel(12, 25, "━");
      setPixel(13, 25, "━");
      setPixel(16, 25, "━");
      setPixel(17, 25, "━");
      setPixel(20, 25, "━");
      setPixel(21, 25, "━");
        setPixel(24, 25, "━");
      setPixel(25, 25, "━");
      setPixel(28, 25, "━");
      setPixel(29, 25, "━");

      setPixel(50, 25, "━");
      setPixel(51, 25, "━");
         setPixel(54, 25, "━");
      setPixel(55, 25, "━");
         setPixel(58, 25, "━");
      setPixel(59, 25, "━");
        setPixel(62, 25, "━");
      setPixel(63, 25, "━");
        setPixel(66, 25, "━");
      setPixel(67, 25, "━");
        setPixel(70, 25, "━");
      setPixel(71, 25, "━");
      

    escribirTextoVertical(4, 6, "CALLE DAMASCO", Color::VERDE_MATRIX);
    setPixel(4, 0, "┃");
    setPixel(4, 2, "┃");
    setPixel(4, 4, "┃");
    setPixel(4, 20, "┃");
    setPixel(4, 22, "┃");
    setPixel(4, 24, "┃");

    // ============================================================
    //  ESQUINA DEL LA VEREDA 
    // ============================================================
    pincel.color = Color::VERDE_MATRIX;
    setPixel(12, 23, "└");

    // ============================================================
    //  ESQUINAS DEL CERRAMIENTO
    // ============================================================
    pincel.color = Color::VERDE_MATRIX;
    setPixel(20, 0, "┌");   // superior izquierda
    setPixel(70, 0, "┐");   // superior derecha
    //setPixel(70, 20, "┘");    // inferior derecha
    setPixel(20, 20, "└");    // inferior izquierda

    // ============================================================
//  ESQUINAS DEL DORMITORIO
// ============================================================
pincel.color = Color::VERDE_MATRIX;
setPixel(28, 0, "┌");   // superior izquierda
setPixel(42, 0, "┐");   // superior derecha
setPixel(42, 6, "┘");  // inferior derecha
setPixel(28, 6, "└");  // inferior izquierda

// ============================================================
//  ESQUINAS DEL PORTON
// ============================================================
pincel.color = Color::VERDE_MATRIX;
setPixel(60, 19, "┌");  // superior izquierda
//setPixel(70, 19, "┐");  // superior derecha
setPixel(60, 21, "└");  // inferior izquierda
setPixel(70, 21, "┘");  // inferior derecha

    actualizarTagsDinamicos();
    imprimirCanvas();
    dibujarTags(tags);
    dibujarTags(tagsDinamicos);

       
    //escribirEnPosicion(50, 2, "C͇̜̞̦̣͕̟̈̍͊̂̉͌̎͗͊O̲̞̟̳̲̲̝̲̥̱͈̭̜̥̞̓͂̽̀Ṋ͔̤͉͔̜̤̟̟͓̔̏̋̄̈́ͅT̫͈͎̘͇̖͍̠̤̰̘͚̈͒̓̏̉̄̒̎̀̓͑͌̒̀̚Ř̤̘̭̩̘͍͙̣̲͕͖̮̫̠̔͌́̄͑O̲͍̯̫̘̪̗͔̠̯̥̲̣͖͛̏̄̂͊̀L̠͖̬͇͗͆̃̇ͅ Ǎ̳͉̱̩̩̟̞̩̖͓͔͍͚̮̳͕̃́̅̚Ṷ̭̭͙̮̣̞̿̑͑͑̋̏̀̇͒̄̐͛̉̃T͎̗̲̞̜̗̤̰͓͍͔͈̣̄̍̀̓͗́̓̀̚Ŏ̦̜̦͔̩̫̎̆̾ͅM̱̜̪͇̰̝̖͓̞͓͕̝̳̓̂̂̅̓̾͋͊͋̾̂͐̋̾͗̚À̜̭̟̱̣̘͔̠̫͇̃̐̒͒͒T̥̤͎͔͖̀̏̐̿̓̌́͊̏̒͗͛͛̓̍̎I͚̜̥̭̤̠̱̩̿̈̔͗̋͗̀C̭͔̗͚̏̑̑̋̓̍̾́́̍́O̤̝͓͉̙̜̱͛̐͐̀͌͂̓̓̓̂̿̀̚ Ḓ̙̥͍͉͖̦̿̓̀́̑Ê̠̳̣̪̖̣̗͉̩̒͒̿͌͊̊͂̌̓̓̒̀ͅ L͙̞̠͙̱̞̳̯̘̟̤̮͉̥̥̐̈̀́̀̌͑̊̾̊͑̑͗̓ͅṲ̘͕͎̲̙̓̿̅̓̾͗͂̌̀̓͐̏̀̾͛͒C͕̫̤͙̪͚͈͍̣̅͆̃̚Ê̩͓̞̗̦̠̤͊͛̌͑̋̓̅̑S̩̳͍̜͈͈͇͖̟̘̓̀̔͒̀͑", Color::VERDE_MATRIX, true);
   
   
   
   
    escribirEnPosicion(50, 2, "S͉̟͇̘̠̟̘̓̔̈́͐͗̒̌̌͐̚ͅI͖̳̥̗̱̩͚̦͔̭͆͌̐̍̉͗͐̏̌S̰̫̖͇̙̓̍́̔̀̃͊̏̇̆Ṭ̲̩͉͙̦͋̍́̑͑͋͂̌̍͛̐ͅE͙̭̘̲̲̠͚̙͓̋̀̌̀͛̎̆̇͐͗ͅͅM̘̗̪̟͔͕͆͗͑̚ͅÅ̗̰̖̯̮̣͖͔̥͍͙̟̉̊̽ D̟̤͔̜̪͖͍̞̜͉͎̙̔̂̿̚É̯̜͇̬͔̜̱̫̲͈͐̇̑̈ L̞̠̲͍̝̱̞̞̘̣͛̊̄͌͆͛̎̾́̐̆̅U͍̥͇͕͎̙͈͊̽̀̏̒C̩̣̭͉͚̩͕͖͐̅̓͐̐͐̚È͚͉̲̫̫͇̰̽̐̇͗̚S̲͓͖͇̬̫̬͍̦͉̮̱͑̆̀̉̐̈́ A̰̤̲̱̓͋̈̎̓̾͒̓̃͐͊̉Ü̮̞̘͈͗̈͂̿̓̓̀͋͒T͉͚̣̞̪̪̰͔͉̃̊͑́̄́̄͒̾͂O̲̯͚͇̙̤͉̥̣̳̲̎̏̄̿̾̀̚ͅM̜̦̟͕̟͍̳̓̓͂̽̐̊̈́͂̎Ạ̦̫̣̗̮̯͔̖̩͛̐̊̎̌̈͗̈͑̚T̰̬̙̘̀̒̓͂̋̓̔̒̈I̙̙̮̭͍̘̮̫͖̜̱̍̿̆̊̓̄͐C̬̗̱͔̜̙̣̿͋͐̅̈͂̎̆ͅͅA̟̟͖̱̤͇͇̒̈́̋͑͆S̞͔̟͈͓̎͂̔̈", Color::VERDE_MATRIX, true);
   
   
   
   
   
    
    
    
    mostrarEstadisticasYPrompt();
}
