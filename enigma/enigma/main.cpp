#include "enigma.h"
#include <iostream>
#include <cctype>
#include <string>
#include <fstream>

// Convierte letra 'A'-'Z' a índice 0-25, si inválida devuelve -1
int letraAIndice(char c) {
    if (c >= 'A' and c <= 'Z') return c - 'A';
    if (c >= 'a' and c <= 'z') return c - 'a';
    return -1;
}

// Limpia y prepara el mensaje: mayúsculas, solo A-Z
std::string prepararMensaje(const std::string& msg) {
    std::string resultado;
    for (char c : msg) {
        if (std::isalpha(c)) {
            resultado += std::toupper(c);
        }
    }
    return resultado;
}

// Pide posiciones iniciales como letras (ejemplo: A C B)
void pedirPosicionesIniciales(int& pos1, int& pos2, int& pos3) {
    std::string entrada;
    bool valido = false;

    while (!valido) {
        std::cout << "Introduce las 3 letras de posicion inicial de los rotores (Ejemplo: A C B): ";
        std::getline(std::cin, entrada);

        if (entrada.size() < 3) {
            std::cout << "[ERROR] Entrada muy corta.\n";
            continue;
        }

        
        int count = 0;
        char letras[3];
        for (char c : entrada) {
            if (std::isalpha(c)) {
                letras[count++] = std::toupper(c);
                if (count == 3) break;
            }
        }
        if (count != 3) {
            std::cout << "[ERROR] Debes ingresar 3 letras.\n";
            continue;
        }

        pos1 = letraAIndice(letras[0]);
        pos2 = letraAIndice(letras[1]);
        pos3 = letraAIndice(letras[2]);

        if (pos1 == -1 || pos2 == -1 || pos3 == -1) {
            std::cout << "[ERROR] Letras inválidas.\n";
            continue;
        }

        valido = true;
    }
}

void mostrarMenu() {
    std::cout << "\n==== MAQUINA ENIGMA ====\n";
    std::cout << "1. Cifrar mensaje\n";
    std::cout << "2. Descifrar mensaje\n";
    std::cout << "3. Editar posición inicial de rotores\n";
    std::cout << "4. Salir\n";
    std::cout << "Selecciona una opcion: ";
}

int main() {
    Rotor r1 = loadRotorFromFile("rotor1.txt");
    Rotor r2 = loadRotorFromFile("rotor2.txt");
    Rotor r3 = loadRotorFromFile("rotor3.txt");

    int opcion = 0;
    int pos1 = 0, pos2 = 0, pos3 = 0;

    do {
        mostrarMenu();
        std::string entrada;
        std::getline(std::cin, entrada);
        try {
            opcion = std::stoi(entrada);
        }
        catch (...) {
            opcion = 0;
        }

        if (opcion == 1) { 
            pedirPosicionesIniciales(pos1, pos2, pos3);

            r1.position = pos1;
            r2.position = pos2;
            r3.position = pos3;

            std::string mensaje;
            std::cout << "Escribe el mensaje que quieres cifrar: ";
            std::getline(std::cin, mensaje);

            std::string limpio = prepararMensaje(mensaje);

            Rotor temp1 = r1;
            Rotor temp2 = r2;
            Rotor temp3 = r3;

            std::string cifrado = encodeMessage(limpio, temp1, temp2, temp3);

            std::cout << "Mensaje cifrado: " << cifrado << "\n";

            std::ofstream archivo("xifrat.txt");
            archivo << prepareMessageToSaveOnFile(cifrado) << std::endl;
            archivo.close();

            mostrarMensaje("xifrat.txt", cifrado);

        }
        else if (opcion == 2) { // Descifrar
            pedirPosicionesIniciales(pos1, pos2, pos3);

            r1.position = pos1;
            r2.position = pos2;
            r3.position = pos3;

            std::string mensaje;
            std::cout << "Escribe el mensaje que quieres descifrar: ";
            std::getline(std::cin, mensaje);

            std::string limpio = prepararMensaje(mensaje);

            Rotor temp1 = r1;
            Rotor temp2 = r2;
            Rotor temp3 = r3;

            
            std::string descifrado = encodeMessage(limpio, temp1, temp2, temp3);

            std::cout << "Mensaje descifrado: " << descifrado << "\n";

            std::ofstream archivo("desxifrat.txt");
            archivo << prepareMessageToSaveOnFile(descifrado) << std::endl;
            archivo.close();

            mostrarMensaje("desxifrat.txt", descifrado);

        }
        else if (opcion == 3) {
            std::cout << "Esta opción permite modificar la posición inicial de los rotores.\n";
            pedirPosicionesIniciales(pos1, pos2, pos3);
            std::cout << "Posiciones iniciales guardadas para esta sesión.\n";
           
        }
        else if (opcion == 4) {
            std::cout << "Saliendo...\n";
        }
        else {
            std::cout << "[ERROR] Opción inválida.\n";
        }

    } while (opcion != 4);

    return 0;
}
