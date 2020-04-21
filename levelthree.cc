#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "block.h"
#include "levels.h"
#include "levelthree.h"
#include <random>
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
using namespace std;

// Refer to levels.h for function explanations 

shared_ptr<Block> levelthree::createBlock()
{
    // Read from file if norandom option is enabled 
    if (this->norandom)
    {
        char nowBlock = block_file.at(this->curseq);
        this->curseq++;
        // go through the same sequence if reached the end of sequence
        if (this->curseq >= block_file.size())
        {
            this->curseq = 0;
        }
        return this->makeBlocks(nowBlock, this->isHeavy());
    }
    else
    {
        // randomly generate number 
        int generateLucky = rand()%9+1; 
        if (generateLucky == 1 || generateLucky == 2)
        {
            return this->makeBlocks('S', this->isHeavy());
        }
        else if (generateLucky == 3 || generateLucky == 4)
        {
            return this->makeBlocks('Z', this->isHeavy());
        }
        else if (generateLucky == 5)
        {
            return this->makeBlocks('I', this->isHeavy());
        }
        else if (generateLucky == 6)
        {
            return this->makeBlocks('J', this->isHeavy());
        }
        else if (generateLucky == 7)
        {
            return this->makeBlocks('L', this->isHeavy());
        }
        else if (generateLucky == 8)
        {
            return this->makeBlocks('O', this->isHeavy());
        }
        else
        {
            return this->makeBlocks('T', this->isHeavy());
        }
    }
}

// Implementing methods
shared_ptr<Block> levelthree::makeBlocks(char type, bool isHeavy)
{
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
bool levelthree::is_file_exist(const string file)
{
    ifstream infile{file};
    return (infile.good());
}

void levelthree::blocksFromFile(string filename)
{
    //  controller will pass these to level
    if (this->norandom)
    {
        if (is_file_exist(filename))
        {
            ifstream file{filename};
            char t;
            while (file >> t)
            {
                block_file.emplace_back(t);
            }
        }
        else
        {
            string s;
            if (filename != "")
            {
                s = "File does not exist or is not readable";
            }
            else
            {
                s = "Empty filename";
            }
            throw(s);
        }
    }
    // Do nothing otherwise 
}

void levelthree::setRandom(bool val) {
    this->norandom = val; 
}

bool levelthree::getRandom() {
    return this->norandom;
}

void levelthree::clearVector() {
    block_file.clear(); 
    this->curseq = 0; 
}

bool levelthree::isHeavy() { return true; }

levelthree::~levelthree() {}
