#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>

#ifndef TWO_H
#define TWO_H

class Block{};

class leveltwo: public levels { 
    Block *createBlock() override; 
    Block *makeBlocks(std::string type, bool isHeavy) override; 
    bool isHeavy() override; 
    ~leveltwo();
};


#endif 
