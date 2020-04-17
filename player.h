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
#include "levelfive.h"
#include "levelsix.h"


class Player { 
    int score;
    std::string name;
    levels *l;
    int level;
    bool blind;
    std::string file;
    Block *b = nullptr;
    Block *bnext = nullptr;
    bool specialCommandHeavy = false;
    public:
    std::string getFileName();
    Player(int, std::string, int, std::string);
    int getScore();
    void addScore(int);
    Block *getBlock();
    bool isBlind();
    void setBlind();
    Block *getNextBlock();
    void setBlock(Block *b);
    void setNextBlock(Block *b);
    void setSpecialHeavy(bool);
    bool isSpecialHeavy();
    std::string getName();
    levels *getPtrLevel();
    int getLevel();
    void changeLevel(int);
    ~Player();
};


#endif
