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
using namespace std; 

// Refer to levels.h for function explanations 

shared_ptr<Block> levelfour::createBlock() {
  // Read from file norandom == true 
  if (this->norandom) {
      char nowBlock = block_file.at(this->curseq); 
       this->curseq++;
       // go through the same sequence if reached the end of sequence 
       if (this->curseq >= block_file.size()) { 
           this->curseq = 0; 
       } 
       return this->makeBlocks(nowBlock, this->isHeavy()); 
  } else {
    // randomly generate using the probabilities given 
    int generateLucky = rand()%9+1; 
    if (generateLucky == 1 || generateLucky == 2) {
        return this->makeBlocks('S', this->isHeavy());
    }
    else if (generateLucky== 3 || generateLucky == 4) {
        return this->makeBlocks('Z', this->isHeavy()); 
    }
    else if(generateLucky==5) {
        return this->makeBlocks('I', this->isHeavy());
    } 
    else if(generateLucky==6) {
        return this->makeBlocks('J', this->isHeavy());
    }
    else if(generateLucky==7) {
        return this->makeBlocks('L', this->isHeavy());
    } 
    else if(generateLucky==8) {
        return this->makeBlocks('O', this->isHeavy());
    } 
    else {
        return this->makeBlocks('T', this->isHeavy());
    }
  }
}

// Implementing methods 
shared_ptr<Block> levelfour::makeBlocks(char type, bool isHeavy) {
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

// check if file exists 
bool levelfour::is_file_exist(const string file) {
    std::ifstream infile(file);  
    return infile.good();
}

void levelfour::blocksFromFile(string filename) {
    if (this->norandom) { 
        //  controller will pass these to level
        if (is_file_exist(filename)) {
            ifstream file{filename};
            char t; 
            while(file>>t) {
                block_file.emplace_back(t); 
            }
        }
        else {
            string s; 
            if (filename!="") {
                s = "File does not exist or is not readable";
            }
            else { s = "Empty filename"; }
            throw(s);
        }
   }
   // Do nothing otherwise; 
}

void levelfour::setRandom(bool val) {
    this->norandom = val; 
}

bool levelfour::getRandom() {
    return this->norandom;
}

bool levelfour::isHeavy() { 
    return true; 
} 

void levelfour::clearVector() {
    block_file.clear(); 
    this->curseq = 0; 
}

levelfour::~levelfour() {}

