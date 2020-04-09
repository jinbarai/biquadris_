#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include "leveltwo.h"
#include <random>

using namespace std; 

Block *leveltwo::createBlock() {
  // generate a number from 0-6 
    int generateLucky = rand()% 7;
    if (generateLucky == 0) {
        return this->makeBlocks('S', this->isHeavy());
    }
    else if (generateLucky==1) {
        return this->makeBlocks('Z', this->isHeavy()); 
    }
    else if(generateLucky==2) {
        return this->makeBlocks('I', this->isHeavy());
    } 
    else if(generateLucky==3) {
        return this->makeBlocks('J', this->isHeavy());
    }
    else if(generateLucky==4) {
        return this->makeBlocks('L', this->isHeavy());
    } 
    else if(generateLucky==5) {
        return this->makeBlocks('O', this->isHeavy());
    } 
    else if(generateLucky==6) {
        return this->makeBlocks('T', this->isHeavy());
    }
}

// Implementing methods 
Block* leveltwo::makeBlocks(char type, bool isHeavy) {
    // create a new block pointer inside level 0
    // depends on how the block class is made
    // return a block pointer 
    Block *p;
    return p; 
} 

bool leveltwo::isHeavy() { return false; } 

leveltwo::~leveltwo() {}

