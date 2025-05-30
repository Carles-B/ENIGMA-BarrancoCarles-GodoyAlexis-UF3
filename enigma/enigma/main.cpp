#include "enigma.h"
#include <iostream>
#include <cctype>

// Muestra el menú principal
void mostrarMenu() {
    std::cout << "\n==== MAQUINA ENIGMA ====\n";
    std::cout << "1. Cifrar mensaje\n";
    std::cout << "2. Descifrar mensaje\n";
    std::cout << "3. Editar posicion inicial del rotor\n";
    std::cout << "4. Salir\n";
    std::cout << "Selecciona una opcion: ";
}

// Convierte una cadena a mayúsculas y elimina espacios
std::string prepararMensaje(const std::string& msg) {
    std::string resultado;
    for (char c : msg) {
        if (std::isalpha(c)) {
            resultado += std::toupper(c);
        }
    }
    return resultado;
}

// Muestra las posiciones actuales de los rotores
void mostrarPosiciones(const Rotor& r1, const Rotor& r2, const Rotor& r3) {
    std::cout << "Posiciones actuales -> Rotor1: " << r1.position
        << ", Rotor2: " << r2.position
        << ", Rotor3: " << r3.position << "\n";
}

int convertirAInt(const std::string& entrada) {
    try {
        return std::stoi(entrada); // Convierte la cadena a un entero
    }
    catch (std::exception& e) {
        return -1; // Si hay error, devolvemos un valor inválido
    }
}
int obtenerNummeroAbecedario(std::string entrada, std::string message) {
    int opcion;
  
    do
    {
        std::cout << message;
        std::getline(std::cin, entrada);
        opcion = convertirAInt(entrada);
        if (opcion < 0 || opcion > 25) {
            std::cout << "Error en el numero ingresado, por favor agrega un numero dentro del rango solicitado" << std::endl;
        }
    } while (opcion < 0  || opcion > 25);
    return opcion;
}


void insertarDatosEnFile(const std::string & mensaje, const std::string & nombreArchivo) {
    std::ofstream file(nombreArchivo, std::ios::app); // Abre el archivo en modo agregar (append)

    if (file.is_open()) {
        file << mensaje << std::endl; // Escribe el mensaje en el archivo
        file.close();
        std::cout << "[OK] Datos guardados en \"" << nombreArchivo << "\" correctamente." << std::endl;
    }
    else {
        std::cerr << "[ERROR] No se pudo abrir el archivo \"" << nombreArchivo << "\"." << std::endl;
    }
}


int main() {
    // Cargar rotores desde archivos
    Rotor rotor1 = loadRotorFromFile("rotor1.txt");
    Rotor rotor2 = loadRotorFromFile("rotor2.txt");
    Rotor rotor3 = loadRotorFromFile("rotor3.txt");
    std::string entrada;
    int opcion;
    do {
        mostrarMenu();

        std::getline(std::cin, entrada);
        opcion = convertirAInt(entrada);  
        

        if (opcion == 1) { // Cifrar
            mostrarPosiciones(rotor1, rotor2, rotor3);

            std::string mensaje;
            std::cout << "Escribe el mensaje que quieres cifrar: ";
            std::getline(std::cin, mensaje);

            std::string limpio = prepararMensaje(mensaje);

            Rotor temp1 = rotor1;
            Rotor temp2 = rotor2;
            Rotor temp3 = rotor3;

            std::string cifrado = encodeMessage(limpio, temp1, temp2, temp3);
        
            std::cout << "Mensaje cifrado: " << cifrado << "\n";
            std::string mensajeAGuardar = prepareMessageToSaveOnFile(cifrado);
            insertarDatosEnFile(mensajeAGuardar, "xifrat.txt");
            mostrarMensaje("Se ha guardado el registro en xifrat.txt", mensajeAGuardar);
        }
        else if (opcion == 2) { // Descifrar
            mostrarPosiciones(rotor1, rotor2, rotor3);

            std::string mensaje;
            std::cout << "Escribe el mensaje cifrado: ";
            std::getline(std::cin, mensaje);

            std::string limpio = prepararMensaje(mensaje);

            Rotor temp1 = rotor1;
            Rotor temp2 = rotor2;
            Rotor temp3 = rotor3;

            std::string descifrado = decodeMessage(limpio, temp1, temp2, temp3);
            std::cout << "Mensaje descifrado: " << descifrado << "\n";
            std::string mensajeAGuardar = prepareMessageToSaveOnFile(descifrado);
            insertarDatosEnFile(mensajeAGuardar, "desxifrat.txt");

            mostrarMensaje("Se ha guardado el registro en desxifrat.txt", mensajeAGuardar); 
        }
        else if (opcion == 3) { // Editar posiciones
            std::string message ;

            int p1, p2, p3;

            p1 = obtenerNummeroAbecedario(message, "Posicion inicial Rotor 1 (0-25):");
            p2 = obtenerNummeroAbecedario(message, "Posicion inicial Rotor 2 (0-25):");
            p3 = obtenerNummeroAbecedario(message, "Posicion inicial Rotor 3 (0-25):");


            std::cout << "La posicion del rotor inicial del rotor 1 es: " << p1 << std::endl;
            std::cout << "La posicion del rotor inicial del rotor 2 es: " << p2 << std::endl;
            std::cout << "La posicion del rotor inicial del rotor 3 es: " << p3 << std::endl;

            rotor1.position = p1 % 26;
            rotor2.position = p2 % 26;
            rotor3.position = p3 % 26;
            
            
        }
        else if (opcion == 4) { // Salir
            std::cout << "Saliendo del programa...\n";
        }
        else {
            std::cout << "Opcion no valida. Intenta de nuevo.\n";
        }

    } while (opcion != 4);

    return 0;
}
