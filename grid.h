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
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include <string>


class Grid { 
    Player *p1;
    Player *p2;
    TextDisplay *td = nullptr; // to add TextDisplay
    //Graphics *gr = nullptr; //  to add Graphics
    std::vector<std::vector<Cell>> theGridp1; 
    std::vector<std::vector<Cell>> theGridp2; 
    // vector of vectors of rows of cells 
    public: 
    Player *getPlayer(std::string s);
    friend std::ostream &operator<<(std::ostream &out, const Grid &gr);
    // for output
    void clear(std::string s); // clears any full row 
    bool isFull(std::string s); // will determine whether or not the board is full 
    void init(Player *p1, Player *p2);
    void score(std::string s, int n, int level);
    void update(std::string, Block *b);
    // where s is the player, n is the # of rows, level is the level of the player
    bool isRowFull(int n, std::string s); // n is the row you want to check
    //void changeLevel(int n, std::string s);
    void move();
    ~Grid();
};
#endif
