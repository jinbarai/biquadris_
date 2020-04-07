#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Block.h"
#include "levels.h"
#include "levelfour.h"
#include <random>

using namespace std; 

Block* levelfour::createBlock() {
  // generate a number from 0-8 
    int generateLucky = rand()% 8;
    if (generateLucky == 0 || generateLucky == 2) {
        return this->makeBlocks("S", this->isHeavy());
    }
    else if (generateLucky==1 || generateLucky == 3) {
        return this->makeBlocks("Z", this->isHeavy()); 
    }
    else if(generateLucky==4) {
        return this->makeBlocks("I", this->isHeavy());
    } 
    else if(generateLucky==5) {
        return this->makeBlocks("J", this->isHeavy());
    }
    else if(generateLucky==6) {
        return this->makeBlocks("L", this->isHeavy());
    } 
    else if(generateLucky==7) {
        return this->makeBlocks("O", this->isHeavy());
    } 
    else if(generateLucky==8) {
        return this->makeBlocks("T", this->isHeavy());
    }
}

// Implementing methods 
Block* levelfour::makeBlocks(string type, bool isHeavy) {
    // create a new block pointer inside level 0
    // depends on how the block class is made
    // return a block pointer 
    Block *p;
    return p; 
} 

bool levelfour::isHeavy() { return true; } 

levelfour::~levelfour() {}

