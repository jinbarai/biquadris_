#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Block.h"
#include "levels.h"
#include <random>

#ifndef ZERO_H
#define ZERO_H


class levelzero:levels {
    int curseq; 
    Block *createBlock() override; 
    Block *makeBlocks(std::string type, bool isHeavy) override;
    void blocksFromFile(std::string filename) override; 
    bool isHeavy() override; 
    ~levelzero();
};


#endif 
