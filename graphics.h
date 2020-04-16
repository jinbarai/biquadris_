#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "player.h"
#include "window.h"
#include "block.h"
#include "state.h"

class Graphics {
    // has a player
    Player *p1;
    Player *p2;
    Xwindow xw;
    public:
    Graphics(Player *p1, Player *p2);
    void notify(State, int row, int col, char c);
    void notifyScore();
    int getColour(char c);
    void changeLevel();
    ~Graphics() = default;
};

#endif

