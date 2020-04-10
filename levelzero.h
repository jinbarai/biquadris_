#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>

#ifndef ZERO_H
#define ZERO_H

class levelzero: public levels {
    int curseq = 0;
    Block *createBlock() override; 
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    void blocksFromFile(std::string filename);
    ~levelzero();
};


#endif 
