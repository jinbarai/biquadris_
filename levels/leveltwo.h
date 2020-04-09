#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Block.h"
#include "levels.h"
#include <random>

#ifndef TWO_H
#define TWO_H


class leveltwo:levels { 
    Block *createBlock() override; 
    Block *makeBlocks(std::string type, bool isHeavy) override; 
    bool isHeavy() override; 
    ~leveltwo();
};


#endif 
