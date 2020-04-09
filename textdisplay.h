#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include "cell.h"
#include "level.h"
#include "controller.h"

class TextDisplay { 
    Level *l = nullptr;
    std::vector<std::vector<char>> theDisplay;
    public: 
    TextDisplay(level *l); //ctor 
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    void notify(int row, int col, char c); // call notify on all cells
    ~TextDisplay();
}

#endif
