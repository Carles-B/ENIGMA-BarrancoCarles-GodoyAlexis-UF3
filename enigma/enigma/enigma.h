#pragma once
#include "Rotor.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


// Carga un rotor desde un archivo de texto
Rotor loadRotorFromFile(const std::string& filename);


std::string encodeMessage(const std::string& missatge, Rotor& r1, Rotor& r2, Rotor& r3);


char reflejar(char c); // nueva funcion reflector


std::string prepareMessageToSaveOnFile(const std::string& missatge);

void mostrarMensaje(const std::string& nombreArchivo, const std::string& mensaje);
