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
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    bool is_file_exist(const string file); 
    public:
    Block *createBlock() override; 
    void blocksFromFile(std::string filename) override;
    ~levelzero();
};


#endif 
