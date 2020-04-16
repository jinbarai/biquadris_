#ifndef GRID_H
#define GRID_H
#include <vector>
#include "cell.h"
#include "state.h"
#include "levels.h"
#include "textdisplay.h"
#include "player.h"
#include "block.h"
#include "graphics.h"

class Grid { 
    Player *p = nullptr;
    TextDisplay *td = nullptr; // to add TextDisplay
    bool text = true;
    Graphics *gr = nullptr; //  to add Graphics
    std::vector<std::vector<Cell>> theGrid;
    // vector of vectors of rows of cells 
    public: 
    void init(Player *p);
    Player *getPlayer();
    friend std::ostream &operator<<(std::ostream &out, const Grid &gr);
    // for output
    void clear(State p, int row, int col);
    void rowclear(State p); // clears any full row 
    bool isFull(); // will determine whether or not the board is full 
    void score(int n, int level);
    void update(State p);
    void setTD(TextDisplay *td);
    void setGraphics(Graphics *gr);
    // where s is the player, n is the # of rows, level is the level of the player
    bool isRowFull(int n); // n is the row you want to check
    //void changeLevel(int n, std::string s);
    bool move(State p, int dir);
    bool validate(int x, int y);
    void rotate(State p);
    Graphics *getGraphics();
    void drop(State p);
    int down(State p);
    ~Grid();
};
#endif
