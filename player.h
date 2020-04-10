#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "levels.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"



class Player { 
    int score;
    string name;
    levels *l;
    int level;
    public:
    Player(int, std::string, int);
    int getScore();
    void addScore(int);
    std::string getName();
    levels *getPtrLevel();
    int getLevel();
    void changeLevel(int);
};


#endif
