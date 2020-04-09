#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>

#ifndef ONE_H
#define ONE_H


class levelone: public levels { 
    Block *createBlock() override; 
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    ~levelone();
};


#endif 
