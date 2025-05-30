#include "enigma.h"
 
std::string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
// Gira el rotor una posicion (como un odometro)


// Convierte 'A'-'Z' a 0-25

// Carga un rotor desde un archivo con una linea de 26 letras mayusculas
Rotor loadRotorFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string wiring;
    if (file >> wiring && wiring.size() == 26) {
        return Rotor(wiring);
    }
    else {
        std::cerr << "Error al cargar el rotor desde " << filename << "\n";
        return Rotor("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); // wiring por defecto
    }
}

// Reflector B (estandar de la Enigma real)
char reflejar(char c) {
    
    return reflector[charToIndex(c)];
} 

// Funcion principal para cifrar
std::string encodeMessage(const std::string& mensaje, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string resultado;

    for (char c : mensaje) {
        if (c < 'A' || c > 'Z') continue;

        // Paso hacia adelante por los rotores
        char letra = r1.encode(c);
        letra = r2.encode(letra);
        letra = r3.encode(letra);
        // Reflector
         letra = reflejar(letra);


        resultado += letra;

        // Rotacion tipo odometro
        r1.rotate();
        if (r1.position == 0) {
            r2.rotate();
            if (r2.position == 0) {
                r3.rotate();
            }
        }
    }

    return resultado;
}

// Funcion principal para descifrar
std::string decodeMessage(const std::string& missatge, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string resultat;

    for (char c : missatge) {
        if (c < 'A' || c > 'Z') continue;
        //Cargando la inversa en el reflector
        int idx = reflector.find(c);
        char letra = indexToChar(idx);

        //Cargando la inversa del rotor 3
        letra = r3.decode(letra);

        //Cargando la inversa del rotor 2
        letra = r2.decode(letra);


        //Cargando la inversa del rotor 1
        letra = r1.decode(letra);


        resultat += letra;

        r1.rotate();
        if (r1.position == 0) {
            r2.rotate();
            if (r2.position == 0) {
                r3.rotate();
            }
        }
    }
    return resultat;
}
std::string prepareMessageToSaveOnFile(const std::string& missatge) {
    std::string finalWord;
    int cnt = 0;

    for (char c : missatge) {
        finalWord += c;
        cnt++;

        // Agrega un espacio cada 5 caracteres
        if (cnt % 5 == 0) {
            finalWord += ' ';
        }
    }

    return finalWord;
}


void mostrarMensaje(const std::string& nombreArchivo, const std::string& mensaje) {
    std::cout << mensaje.length() << std::endl;
    int cantidadLetras = mensaje.length();
    int gruposDeCinco = cantidadLetras / 5 + (cantidadLetras % 5 != 0 ? 1 : 0); // Redondear hacia arriba si hay sobrante

    std::cout << "[OK] \"" << nombreArchivo << "\" ("
        << cantidadLetras << " Letras, " << gruposDeCinco << " grupos de 5)" << std::endl;
}

