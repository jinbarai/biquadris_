#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>
#include "iblock.h"
/*
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
*/
#ifndef ONE_H
#define ONE_H

//class InvalidMove{};

class levelone: public levels { 
    Block *createBlock() override; 
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    void blocksFromFile(std::string filename) override; 
    ~levelone();
};


#endif 
