#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include "levelfour.h"
#include <random>
#include "iblock.h"
/*
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
*/

using namespace std; 

Block* levelfour::createBlock() {
  // generate a number from 0-8 
    int generateLucky = rand()% 8;
    if (generateLucky == 0 || generateLucky == 2) {
        return this->makeBlocks('S', this->isHeavy());
    }
    else if (generateLucky==1 || generateLucky == 3) {
        return this->makeBlocks('Z', this->isHeavy()); 
    }
    else if(generateLucky==4) {
        return this->makeBlocks('I', this->isHeavy());
    } 
    else if(generateLucky==5) {
        return this->makeBlocks('J', this->isHeavy());
    }
    else if(generateLucky==6) {
        return this->makeBlocks('L', this->isHeavy());
    } 
    else if(generateLucky==7) {
        return this->makeBlocks('O', this->isHeavy());
    } 
    else if(generateLucky==8) {
        return this->makeBlocks('T', this->isHeavy());
    }
}

// Implementing methods 
Block* levelfour::makeBlocks(char type, bool isHeavy) {
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

bool levelfour::isHeavy() { 
    return true; 
} 

levelfour::~levelfour() {}

