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
#ifndef FOUR_H
#define FOUR_H

class levelfour: public levels { 
    int curseq = 0; 
    std::shared_ptr<Block> makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    bool norandom = false;
    public: 
    void setRandom(bool val) override; 
    bool getRandom() override; 
    std::shared_ptr<Block> createBlock() override; 
    bool is_file_exist(const std::string file); 
    void clearVector() override; 
    void blocksFromFile(std::string filename) override; 
    ~levelfour();
};


#endif 
