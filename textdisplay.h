#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include "state.h"
#include "player.h"

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
    ~TextDisplay();
};

#endif

