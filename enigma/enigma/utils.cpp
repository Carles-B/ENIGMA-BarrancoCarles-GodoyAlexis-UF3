#include "Utils.h";


int charToIndex(char c) {
    return c - 'A';
}

// Convierte 0-25 a 'A'-'Z'
char indexToChar(int index) {
    return 'A' + index;
}