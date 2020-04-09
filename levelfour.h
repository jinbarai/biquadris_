#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>

#ifndef FOUR_H
#define FOUR_H

class levelfour: public levels { 
    Block *createBlock() override; 
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    ~levelfour();
};


#endif 
