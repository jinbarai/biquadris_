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
    protected:
    std::vector<char> block_file;  // sequence from file
    public:
    int curLevel;
    virtual Block *createBlock() = 0; 
    virtual Block *makeBlocks(char type, bool isHeavy) = 0;
    virtual bool isHeavy()=0; 
    virtual ~levels() = 0; 
};

#endif

/*
Side notes:
- You will create a Level Pointer and acces curLevel to get the curLevel of the game/something on these lines: like Level *l = new Level (avoid heap/find an alternate way to go about it)
int current = l->curLevel. Since curLevel is a field of the class Levels it should be accessible by just creating a levels pointer. 
- Need to figure out a way to call makeBlocks **** 
- Inside Particular Level makeBlocks(this->generateBlockChar, this->isHeavy)
- Each level contains methods such as generateBlockChar that return a character based on the probability, and isHeavy that returns true or false depending on level
- Need a method called blocksFromFile(str filename) ; this will generate a vector of type char reading each Block type from filename 
- createBlocks for levelzero goes through the sequence makeBlocks reads this popped vector 
- Need to figure where and when getBlocksFromFile will be called. Do we also need a  

*/
