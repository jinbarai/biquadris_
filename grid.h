#ifndef GRID_H
#define GRID_H
#include <vector>
#include "textdisplay.h"
#include "cell.h"
#include "levels.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "player.h"
#include <string>

class InvalidMove{}; // for exceptions

class Grid { 
    Player *p1;
    Player *p2;
    TextDisplay *td = nullptr; // to add TextDisplay
    //Graphics *gr = nullptr; //  to add Graphics
    std::vector<std::vector<Cell>> theGridp1; 
    std::vector<std::vector<Cell>> theGridp2; 
    // vector of vectors of rows of cells 
    public: 
    ~Grid();
    Player *getPlayer(std::string s);
    friend std::ostream &operator<<(std::ostream &out, const Grid &gr);
    // for output
    void clear(); // clears any full row 
    bool isFull(std::string s); // will determine whether or not the board is full 
    void init(Player *p1, Player *p2);
    bool isRowFull(int n, std::string s); // n is the row you want to check
    //void changeLevel(int n, std::string s);
};
#endif
