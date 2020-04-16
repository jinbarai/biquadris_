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

void TextDisplay::notify(State p, int row, int col, char c) { 
    if (p == State::p1) { 
        theDisplayp1.at(row).at(col) = c;
    } else { 
        theDisplayp2.at(row).at(col) = c;
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
    out << endl;
    bool f1 = td.p1->isBlind();
    bool f2 = td.p2->isBlind();
    for (int i = 17; i >= 0; --i) {
        for (int k = 0; k < 11; ++k) {
            if (f1) {
                if ((i >= 2 && i <= 11) && (k >= 2 && k <= 8)) {
                    out << '?';
                } else {
                    out << td.theDisplayp1.at(i).at(k);   
                }
            }
            else { 
                out << td.theDisplayp1.at(i).at(k);
            }
        }
        for (int i = 0; i < 8; ++i) { out <<  ' '; }
        for (int k = 0; k < 11; ++k) {
            if (f2) {
                if ((i >= 2 && i <= 11) && (k >= 2 && k <= 8)) {
                    out << '?';
                } else {
                    out << td.theDisplayp2.at(i).at(k);   
                }
            }
            else { 
                out << td.theDisplayp2.at(i).at(k);
            }
        }
        out << endl;
    } 
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    for (int i = 0; i < 8; ++i) { out <<  ' '; } // creates the bottom border
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    out << endl;
    out << "Next:";
    for (int i = 0; i < 14; ++i) { out <<  ' '; } 
    out << "Next:" << endl;
    if (td.p1->getNextBlock()) { 
        td.p1->getNextBlock()->printBlock(0);
    } else { 
        for (int i = 0; i < 11; ++i) { out <<  ' '; }
    } 
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    if (td.p2->getNextBlock()) {
        td.p2->getNextBlock()->printBlock(0);
    } else { 
        for (int i = 0; i < 11; ++i) { out <<  ' '; }
    }
    out << endl;
    if (td.p1->getNextBlock()) { 
        td.p1->getNextBlock()->printBlock(1);
    } else { 
        for (int i = 0; i < 11; ++i) { out <<  ' '; }
    } 
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    if (td.p2->getNextBlock()) {
        td.p2->getNextBlock()->printBlock(1);
    } else { 
        for (int i = 0; i < 11; ++i) { out <<  ' '; }
    }
    out << endl;
    out << endl;
    return out;
}

TextDisplay::~TextDisplay() {
    theDisplayp1.clear();
    theDisplayp2.clear();
}

