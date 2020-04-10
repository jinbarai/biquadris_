#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "levels.h"


class Player { 
    int score;
    string name;
    levels *l;
    int level;
    public:
    Player(int, std::string, levels *, int);
    int getScore();
    void addScore(int);
    std::string getName();
    levels *getPtrLevel();
    int getLevel();
    void changeLevel(levels *, int);
};


#endif
