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
    void blindnotify(State, int row, int col, char c);
    void notifyScore();
    void drawBlind(State p);
    int getColour(char c);
    void next(); // updates the next block
    void NextBlockp1(char c);
    void level6(State p);
    void NextBlockp2(char c);
    void changeLevel();
    ~Graphics() = default;
};

#endif

