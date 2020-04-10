#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include "cell.h"
#include "levels.h"
#include "player.h"
#include <string>

class TextDisplay { 
    Player *p1;
    Player *p2;
    std::vector<std::vector<char>> theDisplayp1;
    std::vector<std::vector<char>> theDisplayp2;
    public: 
    TextDisplay(Player *p1, Player *p2); //ctor 
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    void notify(std::string s, int row, int col, char c); // call notify on all cells
    ~TextDisplay();
};

#endif
