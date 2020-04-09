#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include "levelone.h"
#include <random>

using namespace std; 

Block* levelone::createBlock() {
  // generate a number from 1-6 
    int generateLucky = rand()% 6 + 1;
    if (generateLucky == 1) {
        int n = rand()% 2 + 1; 
        if (n==1) {
            return this->makeBlocks('S', this->isHeavy());
        }
        else {
            return this->makeBlocks('Z', this->isHeavy()); 
        }
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
Block* levelone::makeBlocks(char type, bool isHeavy) {
    // create a new block pointer inside level 0
    // depends on how the block class is made
    // return a block pointer 
    Block *p;
    return p; 
} 

bool levelone::isHeavy() { return false; } 

levelone::~levelone() {}

