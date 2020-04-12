#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "levels.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "block.h"


class Player { 
    int score;
    string name;
    levels *l;
    int level;
    Block *b = nullptr;
    public:
    Player(int, std::string, int);
    int getScore();
    void addScore(int);
    Block *getBlock();
    void setBlock(Block *b);
    std::string getName();
    levels *getPtrLevel();
    int getLevel();
    void changeLevel(int);
    ~Player();
};


#endif
