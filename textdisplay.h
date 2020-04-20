#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include "state.h"
#include "player.h"


/* TEXTDISPLAY
 * This class does not own any other class in particular, but
 * has 2 players (owned by the Grid). The textdisplay class
 * is notified by the grid (refer to grid.cc)
 */

class TextDisplay { 
    std::shared_ptr<Player> p1;
    std::shared_ptr<Player> p2;
    int highscore;
    std::vector<std::vector<char>> theDisplayp1;
    std::vector<std::vector<char>> theDisplayp2;
    public: 
    TextDisplay(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, int score); //ctor 
    void updateScore(int n);
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    void notify(State p, int row, int col, char c); // call notify on all cells
    ~TextDisplay() = default;
};

#endif

