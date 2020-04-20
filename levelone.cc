#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include "levelone.h"
#include <time.h>
#include <random>
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
using namespace std; 

// Refer to levels.h for function explanations 

shared_ptr<Block> levelone::createBlock() {
    // Generate a lucky number using rand()
    int generateLucky = rand()%6+1; 
    // Calculating block types based on probabilities
    if (generateLucky == 1) {
        int n = rand()%2+1; 
        if (n == 1) {
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
    else {
        return this->makeBlocks('T', this->isHeavy());
    }
}

// Implementing methods 
shared_ptr<Block> levelone::makeBlocks(char type, bool isHeavy) {
    shared_ptr<Block> p; 
    switch(type) {
    case 'I': 
        p = make_shared<IBlock>(isHeavy);
        break;
    case 'J': 
        p = make_shared<JBlock>(isHeavy);
        break;
    case 'L': 
        p = make_shared<LBlock>(isHeavy);
        break;
    case 'O': 
        p = make_shared<OBlock>(isHeavy);
        break;
    case 'S': 
        p = make_shared<SBlock>(isHeavy);
        break;
    case 'Z': 
        p = make_shared<ZBlock>(isHeavy);
        break;
    default: 
        p = make_shared<TBlock>(isHeavy);
        break;
    }
    return p; 
} 

// You can't read from a file for this level 
void levelone::blocksFromFile(string filename) {
    string s = "Invalid level for reading from file";
    throw (s); 
}

bool levelone::getRandom() {
    return this->norandom; 
}

// You cannot read from a file hence norandom=false 
void levelone::setRandom(bool val) {
    this->norandom = false; 
}

bool levelone::isHeavy() {
     return false; 
} 

void levelone::clearVector() {
    block_file.clear(); 
}

levelone::~levelone() {}

