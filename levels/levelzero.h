#ifndef ZERO_H
#define ZERO_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>

class Block{};

class levelzero: public levels {
    int curseq; 
    Block *createBlock() override; 
    Block *makeBlocks(std::string type, bool isHeavy) override;
    void blocksFromFile(std::string filename) override; 
    bool isHeavy() override; 
    ~levelzero();
};


#endif 
