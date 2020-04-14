#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "levels.h"
#include "block.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"


class Player { 
    int score;
    std::string name;
    levels *l;
    int level;
    Block *b = nullptr;
    Block *bnext = nullptr;
    public:
    Player(int, std::string, int);
    int getScore();
    void addScore(int);
    Block *getBlock();
    Block *getNextBlock();
    void setBlock(Block *b);
    void setNextBlock(Block *b);
    std::string getName();
    levels *getPtrLevel();
    int getLevel();
    void changeLevel(int);
    ~Player();
};


#endif
