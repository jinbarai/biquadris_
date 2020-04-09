#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include "cell.h"
#include "levels.h"
#include "controller.h"

class TextDisplay { 
    levels *l = nullptr;
    std::vector<std::vector<char>> theDisplay;
    public: 
    TextDisplay(levels *l); //ctor 
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    void notify(int row, int col, char c); // call notify on all cells
    ~TextDisplay();
};

#endif
