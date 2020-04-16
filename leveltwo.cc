#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include "leveltwo.h"
#include <random>
#include "iblock.h"
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"

using namespace std; 

Block *leveltwo::createBlock() {
    // generate a number from 0-6 
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(1,7); // distribution in range [1, 6]
    int generateLucky = dist6(rng);
    if (generateLucky == 1) {
        return this->makeBlocks('S', this->isHeavy());
    }
    else if (generateLucky==2) {
        return this->makeBlocks('Z', this->isHeavy()); 
    }
    else if(generateLucky==3) {
        return this->makeBlocks('I', this->isHeavy());
    } 
    else if(generateLucky==4) {
        return this->makeBlocks('J', this->isHeavy());
    }
    else if(generateLucky==5) {
        return this->makeBlocks('L', this->isHeavy());
    } 
    else if(generateLucky==6) {
        return this->makeBlocks('O', this->isHeavy());
    } 
    else {
        return this->makeBlocks('T', this->isHeavy());
    }
}

// Implementing methods 
Block* leveltwo::makeBlocks(char type, bool isHeavy) {
      Block *p; 
    switch(type) {
    case 'I': 
        p = new IBlock(isHeavy);
        break;
    case 'J': 
        p = new JBlock(isHeavy);
        break;
    case 'L': 
        p = new LBlock(isHeavy);
        break;
    case 'O': 
        p = new OBlock(isHeavy);
        break;
    case 'S': 
        p = new SBlock(isHeavy);
        break;
    case 'Z': 
        p = new ZBlock(isHeavy);
        break;
    default: 
        p = new TBlock(isHeavy);
        break;
    }
    return p; 
} 

void leveltwo::blocksFromFile(string filename) {   
    string s = "Invalid level for reading from file";
    throw (s); 
}

void leveltwo::setRandom(bool val) {
    this->norandom = false; 
}

bool leveltwo::getRandom() {
    return this->norandom; 
}

bool leveltwo::isHeavy() { return false; } 

leveltwo::~leveltwo() {}

