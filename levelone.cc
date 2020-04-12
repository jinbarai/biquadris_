#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include "levelone.h"
#include <random>
/*
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
*/

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
    Block *p; 
    switch(type) {
    case 'I': p = new IBlock(isHeavy); 
    /*
    case 'J': p = new JBlock(isHeavy);
    case 'L': p = new LBlock(isHeavy);
    case 'O': p = new OBlock(isHeavy);
    case 'S': p = new SBlock(isHeavy);
    case 'T': p = new TBlock(isHeavy);
    default: p = new ZBlock(isHeavy)
    */
    }
    return p; 
} 

void levelone::blocksFromFile(string filename) {
    string s = "Invalid level for reading from file";
    throw (s); 
}

bool levelone::isHeavy() {
     return false; 
} 

levelone::~levelone() {}

