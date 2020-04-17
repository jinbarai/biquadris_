#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "grid.h"
#include "block.h"
#include "levels.h"
#include "graphics.h"
#include "state.h"
// when you cannot spot

class Controller { 
    Grid *g1;
    Grid *g2;
    int highscore;
    bool text;
    TextDisplay *td;
    State turn; //  either p1, or p2
    Graphics *gr = nullptr;
    public: 
    Grid *getGrid();
    Controller(Grid *g1, Grid *g2, TextDisplay *td, int score, bool text, Graphics *gr); 
    // main will make player pointers and pass the grid to the controller. 
    void changeTurn();
    void move(int n, int dir);
    void cw(int n = 1); // clockwise
    void ccw(int n = 1); // counterclockwise
    void levelup();
    void leveldown();
    // Special Actions
    void specialAction();
    void changeBlock(char c);
    void blind();
    void heavy();
    void force(char c);
    void generate();
    Grid *getG1();
    Grid *getG2();
    void startlevel(int n);
    void restart(); 
    void drop(int n = 1);
    void random();
    void clearVector(levels *l);
    void norandom(std::string filename);
    void sequence(std::string filename); 
    void down(int n = 1);
    void readFromFile(std::string file, levels *l); 
    ~Controller();
};

#endif

