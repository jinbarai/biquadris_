#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Block.h"
#include "levels.h"
#include "levelzero.h"
#include <random>

using namespace std; 

Block* levelzero::createBlock() {
       string nowBlock = block_file.at(this->curseq); 
       this->curseq++;
       // go through the same sequence if reached the end of sequence 
       if (this->curseq >= block_file.size()) { 
           this->curseq = 0; 
       } 
       return this->makeBlocks(nowBlock, this->isHeavy()); 
}

// Implementing methods 
Block* levelzero::makeBlocks(string type, bool isHeavy) {
    // create a new block pointer inside level 0
    // depends on how the block class is made
    // return a block pointer 
    Block *p;
    return p; 
} 

// Read from file 
void levelzero::blocksFromFile(string filename) {
    ifstream file{filename};
    string t; 
    while(file>>t) {
        block_file.emplace_back(t); 
    }
}

bool levelzero::isHeavy() { return false; } 

levelzero::~levelzero() {}

