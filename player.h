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


/* PLAYER 
 * A player is owned by a grid
 * but a graphic class and textdisplay class 
 * also have (HAS-A) grid.
 * A player OWNS-A level (this->l) and OWNS 2 block pointers, 
 * the current and next block of the player 
 * (this->b and this->bnext)
 */

class Player { 
    int score;
    const std::string name;
    std::shared_ptr<levels> l;
    int level;
    bool bonus;
    bool blind;
    //bool levelHeavy;
    std::string file;
    std::shared_ptr<Block> b = nullptr;
    std::shared_ptr<Block> bnext = nullptr;
    bool specialCommandHeavy = false;
    public:
    std::string getFileName();
    Player(std::string, int, bool bonus, std::string = "");
    int getScore();
    void addScore(int);
    void changeBonus(bool b);
   // void setLevelHeavy(bool);
   // bool isLevelHeavy();
    std::shared_ptr<Block> getBlock();
    bool isBlind();
    void setBlind();
    std::shared_ptr<Block> getNextBlock();
    void setBlock(std::shared_ptr<Block> b);
    void setNextBlock(std::shared_ptr<Block> b);
    void setSpecialHeavy(bool);
    bool isSpecialHeavy();
    std::string getName();
    std::shared_ptr<levels> getPtrLevel();
    int getLevel();
    void setFile(std::string filename); 
    void changeLevel(int);
    ~Player() = default;
};


#endif
