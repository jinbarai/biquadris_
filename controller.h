#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "grid.h"
#include "block.h"
#include "levels.h"

enum class State { p1 , p2 };
class InvalidMove{}; // for exceptions

struct GameOver{
    State player;
}; 

// when you cannot spot

class Controller { 
    Grid *gr;
    State turn; //  either p1, or p2
    // Graphics *g;
    public: 
    Controller(Grid *g); // grid will make a textdisplay! 
    // main will make player pointers and pass the grid to the controller. 
    void changeTurn();
    void text(); // will cancel graphics
    void left();
    void right();
    void down();
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

