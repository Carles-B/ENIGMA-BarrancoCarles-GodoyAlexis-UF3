#pragma once
#include "utils.h";
#include <iostream>



struct Rotor {
    std::string wiring;  // 26 letras mezcladas
    int position;        // posición inicial (0-25)

    Rotor(std::string wiring_, int position_ = 0) : wiring(wiring_), position(position_) {}

    char encode(char input);
    char decode(char input);
    void rotate();


};