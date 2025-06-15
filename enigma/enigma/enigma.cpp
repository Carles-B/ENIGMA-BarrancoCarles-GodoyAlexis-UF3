#include "enigma.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

std::string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

Rotor loadRotorFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string wiring;
    char notch = 'Z'; // default

    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir " << filename << "endl";
        return Rotor("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, notch);
    }

    std::getline(file, wiring);
    if (wiring.size() != 26) {
        std::cerr << "[ERROR] Wiring incorrecto en " << filename << "\n";
        return Rotor("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, notch);
    }

    std::string notchLine;
    if (std::getline(file, notchLine)) {
        if (!notchLine.empty() && notchLine[0] >= 'A' and notchLine[0] <= 'Z') {
            notch = notchLine[0];
        }
    }

    return Rotor(wiring, 0, notch);
}

char reflejar(char c) {
    return reflector[charToIndex(c)];
}

bool rotorNotchTriggered(char notch, int position) {
    return position == charToIndex(notch);
}

std::string encodeMessage(const std::string& mensaje, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string resultado;

    for (char c : mensaje) {
        if (c < 'A' || c > 'Z') continue;

        // Rotación con notch:
        r1.rotate();

        bool rotor2Turn = rotorNotchTriggered(r1.notch, r1.position);
        if (rotor2Turn) {
            r2.rotate();
            bool rotor3Turn = rotorNotchTriggered(r2.notch, r2.position);
            if (rotor3Turn) {
                r3.rotate();
            }
        }

        // Paso hacia adelante
        char letra = r1.encode(c);
        letra = r2.encode(letra);
        letra = r3.encode(letra);

        // Reflector
        letra = reflejar(letra);

        // Paso hacia atrás
        letra = r3.decode(letra);
        letra = r2.decode(letra);
        letra = r1.decode(letra);

        resultado += letra;
    }

    return resultado;
}

std::string prepareMessageToSaveOnFile(const std::string& missatge) {
    std::string finalWord;
    int cnt = 0;

    for (char c : missatge) {
        finalWord += c;
        cnt++;

        if (cnt % 5 == 0) {
            finalWord += ' ';
        }
    }

    return finalWord;
}

void mostrarMensaje(const std::string& nombreArchivo, const std::string& mensaje) {
    int cantidadLetras = 0;
    for (char c : mensaje) {
        if (c >= 'A' and c <= 'Z') cantidadLetras++;
    }
    int gruposDeCinco = cantidadLetras / 5 + (cantidadLetras % 5 != 0 ? 1 : 0);

    std::cout << "[OK] Missatge " << nombreArchivo << " (" << cantidadLetras
        << " lletres, " << gruposDeCinco << " grups de 5)" << std::endl;
}
