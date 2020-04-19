#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "player.h"
#include "window.h"
#include "block.h"
#include "state.h"

class Graphics {
    // has a player
    std::shared_ptr<Player> p1;
    std::shared_ptr<Player> p2;
    Xwindow xw;
    public:
    Graphics();
    void init(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, int score);
    void notify(State, int row, int col, char c);
    void blindnotify(State, int row, int col, char c);
    void notifyScore();
    void changeScore(int n);
    void drawBlind(State p);
    int getColour(char c);
    void next(); // updates the next block
    void NextBlockp1(char c);
    void level6(State p);
    void NextBlockp2(char c);
    Xwindow *getXwindow();
    void changeLevel();
    ~Graphics() = default;
};

#endif

