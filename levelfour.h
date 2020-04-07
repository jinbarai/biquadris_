#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Block.h"
#include "levels.h"
#include <random>

#ifndef FOUR_H
#define FOUR_H


class levelfour:levels { 
    Block *createBlock() override; 
    Block *makeBlocks(std::string type, bool isHeavy) override; 
    bool isHeavy() override; 
    ~levelfour();
};


#endif 
