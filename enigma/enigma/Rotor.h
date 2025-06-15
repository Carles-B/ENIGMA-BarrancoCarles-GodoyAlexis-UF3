#ifndef ROTOR_H
#define ROTOR_H

#include <string>

struct Rotor {
    std::string wiring;
    int position;
    char notch;

    Rotor(const std::string& wiring_, int position_ = 0, char notch_ = 'Z');
    void rotate();
    char encode(char c) const;
    char decode(char c) const;
};

#endif
