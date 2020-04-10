#include "textdisplay.h"
#include <iostream>
using namespace std;


TextDisplay::TextDisplay(Player *p1, Player *p2) : p1{p1}, p2{p2} {
    theDisplayp1.clear();
    theDisplayp2.clear();
    for (int i = 0; i < 18; ++i) {
        vector<char> c;
        theDisplayp1.emplace_back(c);
        for (int k = 0; k < 11; ++k) {
            theDisplayp1.at(i).emplace_back(' '); 
            // just a space
        }
    }
    for (int i = 0; i < 18; ++i) {
        vector<char> c;
        theDisplayp2.emplace_back(c);
        for (int k = 0; k < 11; ++k) {
            theDisplayp2.at(i).emplace_back(' '); 
            // just a space
        }
    }
}

void TextDisplay::notify(string s, int row, int col, char c) { 
    if (s == "p1") { 
        theDisplayp1.at(row).at(col) = c;
        cout << *this;
    } else { 
        theDisplayp2.at(row).at(col) = c;
        cout << *this;
    }
}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    // print the names
    int size = td.p1->getName().length();
    out << "Name: " << td.p1->getName();
    for (int i = size; i < 5; ++i) { 
        out << " ";
    }
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    out << "Name: " << td.p2->getName() << endl;
    // print the levels
    out << "Level:    " << td.p1->getLevel();
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    out << "Level:    " << td.p2->getLevel() << endl;
    // print the scores
    out << "Score:    "  << td.p1->getScore();
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    out << "Score:    "  << td.p2->getScore() << endl;
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    for (int i = 0; i < 8; ++i) { out <<  ' '; } // creates the top border
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    for (int i = 0; i < 18; ++i) {
        for (int k = 0; k < 11; ++k) {
            out << td.theDisplayp1.at(i).at(k);
        }
        for (int i = 0; i < 8; ++i) { out <<  ' '; }
        for (int k = 0; k < 11; ++k) {
            out << td.theDisplayp2.at(i).at(k);
        }
        out << endl;
    } 
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    for (int i = 0; i < 8; ++i) { out <<  ' '; } // creates the bottom border
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    out << endl;
    return out;
}

TextDisplay::~TextDisplay() {
    theDisplayp1.clear();
    theDisplayp2.clear();
}

