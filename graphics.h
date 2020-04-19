#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "player.h"
#include "window.h"
#include "block.h"
#include "state.h"

/* GRAPHICS
 * uses "window.h"
 * align1 -> Player 1 graphics
 * align2 -> Player 2 graphics 
 */

class Graphics {
    // HAS-A 2 players
    std::shared_ptr<Player> p1;
    std::shared_ptr<Player> p2;
    Xwindow xw;
    public:
    Graphics(); // ctor
    void init(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, int score);
    void notify(State, int row, int col, char c);
    void blindnotify(State, int row, int col, char c);
    void notifyScore();
    void changeScore(int n);
    void drawBlind(State p);
    int getColour(char c);
    void next(); // updates the next block
    void NextBlockp1(char c);
    void NextBlockp2(char c);
    void level6(State p);
    Xwindow *getXwindow();
    void changeLevel();
    ~Graphics() = default;
};

#endif

