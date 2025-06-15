#include "Rotor.h"
#include "Utils.h"

Rotor::Rotor(const std::string& wiring_, int position_, char notch_)
    : wiring(wiring_), position(position_), notch(notch_) {
}

void Rotor::rotate() {
    position = (position + 1) % 26;
}

char Rotor::encode(char c) const {
    int idx = (charToIndex(c) + position) % 26;
    char wired = wiring[idx];
    int result = (charToIndex(wired) - position + 26) % 26;
    return 'A' + result;
}

char Rotor::decode(char c) const {
    int idx = (charToIndex(c) + position) % 26;
    for (int i = 0; i < 26; ++i) {
        if (wiring[i] == 'A' + idx) {
            int result = (i - position + 26) % 26;
            return 'A' + result;
        }
    }
    return c;
}
