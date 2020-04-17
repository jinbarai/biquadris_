#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>
#include "iblock.h"
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"

#ifndef ZERO_H
#define ZERO_H

class levelzero: public levels {
    bool norandom = true; 
    int curseq = 0;
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    bool is_file_exist(const std::string file); 
    public:
    bool getRandom() override; 
    void setRandom(bool val) override; 
    Block *createBlock() override; 
    void clearVector() override;
    void blocksFromFile(std::string filename) override;
    ~levelzero();
};


#endif 