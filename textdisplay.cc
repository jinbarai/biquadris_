#include "textdisplay.h"
#include <iostream>
using namespace std;


TextDisplay::TextDisplay(levels *l) {
    theDisplay.clear();
    this->l = l; 
    for (int i = 0; i < 18; ++i) {
        vector<char> c;
        theDisplay.emplace_back(c);
        for (int k = 0; k < 11; ++k) {
            theDisplay.at(i).emplace_back(' '); 
            // just a space
        }

    }
}

void TextDisplay::notify(int row, int col, char c) { 
    theDisplay.at(row).at(col) = c;
}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = 0; i < 18; ++i) {
        for (int k = 0; k < 11; ++k) {
            out << td.theDisplay.at(i).at(k);
        }
        out << endl;
    } 
    return out;
}

TextDisplay::~TextDisplay() {
    theDisplay.clear();
}