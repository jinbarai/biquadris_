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

Block *levelthree::createBlock()
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
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> dist6(1, 9); // distribution in range [1, 9]
        int generateLucky = dist6(rng);
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
Block *levelthree::makeBlocks(char type, bool isHeavy)
{
    Block *p;
    switch (type)
    {
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
bool levelthree::is_file_exist(const string file)
{
    std::ifstream infile(file);
    return infile.good();
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

bool levelthree::isHeavy() { return true; }

levelthree::~levelthree() {}
