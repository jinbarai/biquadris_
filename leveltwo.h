#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
#ifndef TWO_H
#define TWO_H

//class InvalidMove{}; // use state.h instead

class leveltwo: public levels { 
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    bool norandom = false; 
    public: 
    bool getRandom() override;
    void setRandom(bool val) override; 
    Block *createBlock() override; 
    void clearVector() override; 
    void blocksFromFile(std::string filename) override; 
    ~leveltwo();
};


#endif 
