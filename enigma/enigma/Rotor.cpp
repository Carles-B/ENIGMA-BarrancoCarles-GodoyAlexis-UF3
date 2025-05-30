#include "Rotor.h";
#include <iostream>;


void Rotor::rotate() {
    position = (position + 1) % 26;
}

// Codifica una letra segun la posicion actual del rotor
char Rotor::encode(char input) {
    int index = charToIndex(input);
    int shiftedIndex = (index + position) % 26;
    return wiring[shiftedIndex];
}
char Rotor::decode(char input) {
    int index = wiring.find(input);
    return indexToChar((index - position + 26) % 26);
}

