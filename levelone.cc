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
//https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
Block* levelone::createBlock() {
  // generate a number from 1-6 
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

    int generateLucky;
   // srand (time(NULL));
    generateLucky = dist6(rng);
  //  generateLucky = rand() % 6;
    if (generateLucky == 0) {
        random_device dev2;
        mt19937 rng2(dev2());
        uniform_int_distribution<mt19937::result_type> dist2(1,2); // distribution in range [1, 2]
        int n = dist2(rng2);
        if (n == 1) {
            return this->makeBlocks('S', this->isHeavy());
        }
        else if (n == 2){
            return this->makeBlocks('Z', this->isHeavy()); 
        }
    }
    else if(generateLucky==1) {
        return this->makeBlocks('I', this->isHeavy());
    } 
    else if(generateLucky==2) {
        return this->makeBlocks('J', this->isHeavy());
    }
    else if(generateLucky==3) {
        return this->makeBlocks('L', this->isHeavy());
    } 
    else if(generateLucky==4) {
        return this->makeBlocks('O', this->isHeavy());
    } 
    else if(generateLucky==5) {
        return this->makeBlocks('T', this->isHeavy());
    }
}

// Implementing methods 
Block* levelone::makeBlocks(char type, bool isHeavy) {
    cout << "TYPE:#" << type << "#" << endl;
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

void levelone::blocksFromFile(string filename) {
    string s = "Invalid level for reading from file";
    throw (s); 
}

bool levelone::isHeavy() {
     return false; 
} 

levelone::~levelone() {}

