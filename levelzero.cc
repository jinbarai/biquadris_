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
    case 'I': p = new IBlock(isHeavy); 
    case 'J': p = new JBlock(isHeavy);
    case 'L': p = new LBlock(isHeavy);
    case 'O': p = new OBlock(isHeavy);
    case 'S': p = new SBlock(isHeavy);
    case 'T': p = new TBlock(isHeavy);
    default: p = new ZBlock(isHeavy);
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

levelzero::~levelzero() {}
