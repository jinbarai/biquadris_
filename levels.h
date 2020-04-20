#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"

// Factor Design Method implementation

class levels {
    virtual std::shared_ptr<Block> makeBlocks(char type, bool isHeavy) = 0;
    // Getter function returns if a block is supposed to be heavy or not in that level
    virtual bool isHeavy()=0; 
    // Boolean to see if we would randomly generate the blocks or using a file
    bool norandom = false; 
    protected:
    std::vector<char> block_file;  // sequence from file
    public:
    // Getter function to return bool norandom's value
    virtual bool getRandom()=0; 
    // Setter function to set the value of norandom to val
    virtual void setRandom(bool val)=0; 
    // read blocks from a txt file and store it in blocks_file vector 
    virtual void blocksFromFile(std::string filename) = 0; 
    virtual std::shared_ptr<Block> createBlock() = 0; 
    // Helper method to clear the vector blocks_file and set norandom to false 
    virtual void clearVector()=0; 
    // Destructor
    virtual ~levels() = 0; 
};

#endif
