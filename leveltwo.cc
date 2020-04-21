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

// Refer to levels.h for function explanations 

shared_ptr<Block> leveltwo::createBlock() {
    // generate a number from 0-6 
    int generateLucky = rand()%7+1; 
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
shared_ptr<Block> leveltwo::makeBlocks(char type, bool isHeavy) {
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

void leveltwo::clearVector() {
    block_file.clear(); 
}

bool leveltwo::isHeavy() { return false; } 

leveltwo::~leveltwo() {}

