#ifndef GRID_H
#define GRID_H
#include <vector>
#include "textdisplay.h"
#include "cell.h"
#include "levels/levels.h"
#include "levels/levelzero.h"
#include "levels/levelone.h"
#include "levels/leveltwo.h"
#include "levels/levelthree.h"
#include "levels/levelfour.h"
#include "controller.h"

class InvalidMove{}; // for exceptions

class Grid { 
    const int col = 11;
    const int row = 18; // save three for top 
    levels *level;
    TextDisplay *td = nullptr; // to add TextDisplay
    //Graphics *gr = nullptr; //  to add Graphics
    std::vector<std::vector<Cell>> theGrid; 
    // vector of vectors of rows of cells 
    public: 
    ~Grid();
    friend std::ostream &operator<<(std::ostream &out, const Grid &gr);
    // for output
    void clear(); // clears any full row 
    bool isFull(); // will determine whether or not the board is full 
    void init(size_t n); // n is the level
    bool isRowFull(int n); // n is the row you want to check
    void changeLevel(int n);
};
#endif
