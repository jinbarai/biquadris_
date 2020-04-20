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
    // Boolean to see if we would randomly generate the blocks or using a file
    bool norandom = true; 
    // keeps track of the sequence in the vector of blocks 
    int curseq = 0;
    // Function is explanatory 
    std::shared_ptr<Block> makeBlocks(char type, bool isHeavy) override; 
    // Getter function returns if a block is supposed to be heavy or not in that level
    bool isHeavy() override; 
    // checks if a file exists 
    bool is_file_exist(const std::string file); 
    public:
    // Getter function to return bool norandom's value
    bool getRandom() override; 
    // Setter function to set the value of norandom to val
    void setRandom(bool val) override; 
    std::shared_ptr<Block> createBlock() override; 
    // Helper method to clear the vector blocks_file 
    void clearVector() override;
    // read blocks from a txt file and store it in blocks_file vector 
    void blocksFromFile(std::string filename) override;
    ~levelzero();
};


#endif 