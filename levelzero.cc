#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include "levelzero.h"
#include <random>
#include "iblock.h"
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"


using namespace std; 

Block* levelzero::createBlock() {
       char nowBlock = block_file.at(this->curseq); 
       this->curseq++;
       // go through the same sequence if reached the end of sequence 
       if (this->curseq >= block_file.size()) { 
           this->curseq = 0; 
       } 
       return this->makeBlocks(nowBlock, this->isHeavy()); 
}


// Implementing methods 
Block* levelzero::makeBlocks(char type, bool isHeavy) {
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

// check if file exists 
bool levelzero::is_file_exist(const string file) {
    std::ifstream infile(file);  
    return infile.good();
}

// Read from file 
void levelzero::blocksFromFile(string filename) {
    //  controller will pass these to level
    //cout << "LET'S" << endl; 
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

bool levelzero::isHeavy() { 
    return false; 
} 

void levelzero::clearVector() {
    block_file.clear(); 
}

void levelzero::setRandom(bool val){
    this->norandom = true; 
}   

bool levelzero::getRandom() {
    return this->norandom; 
}

levelzero::~levelzero() {}
