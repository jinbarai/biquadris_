#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>

#ifndef THREE_H
#define THREE_H

class Block{};

class levelthree: public levels { 
    Block *createBlock() override; 
    Block *makeBlocks(std::string type, bool isHeavy) override; 
    bool isHeavy() override; 
    ~levelthree();
};


#endif 
