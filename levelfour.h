#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include <random>
#include "iblock.h"
/*
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
*/
#ifndef FOUR_H
#define FOUR_H

//class InvalidMove{};

class levelfour: public levels { 
    Block *makeBlocks(char type, bool isHeavy) override; 
    bool isHeavy() override; 
    public: 
    Block *createBlock() override; 
    bool is_file_exist(const std::string file); 
    void blocksFromFile(std::string filename) override; 
    ~levelfour();
};


#endif 
