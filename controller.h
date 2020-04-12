#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "grid.h"
#include "block.h"
#include "levels.h"
#include "state.h"

// when you cannot spot

class Controller { 
    Grid *g1;
    Grid *g2;
    State turn; //  either p1, or p2
    // Graphics *g;
    public: 
    Grid *getGrid();
    Controller(Grid *g1, Grid *g2); 
    // main will make player pointers and pass the grid to the controller. 
    void changeTurn();
    void text(); // will cancel graphics
    void left();
    void move(int n, int dir);
    void cw(); // clockwise
    void ccw(); // counterclockwise
    void drop();
    void levelup();
    void leveldown();
    // Special Actions
    void blind();
    void heavy();
    void force();
    void generate();
    void startlevel(int n);
    void restart(); 
    void readFromFile(std::string file, levels *l); 
};

#endif

