#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>
#include "iblock.h"
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"

#ifndef ONE_H
#define ONE_H

//class InvalidMove{};

class levelone: public levels { 
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    bool norandom=false; 
    public: 
    void setRandom(bool val) override;
    bool getRandom() override; 
    Block *createBlock() override; 
    void blocksFromFile(std::string filename) override; 
    ~levelone();
};


#endif 
