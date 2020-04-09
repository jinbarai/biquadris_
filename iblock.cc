#include "iblock.h"
#include <vector>
#include <memory>

extern const int I_BLOCK_WIDTH = 1;
extern const int I_BLOCK_HEIGHT = 4;
extern const int I_BLOCK_SPAWN_X = 6;
extern const int I_BLOCK_SPAWN_Y = 2;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

IBlock::IBlock(bool heavy):
Block(I_BLOCK_HEIGHT, I_BLOCK_WIDTH, 5, 14, {{5,14}, {6,14}, {7,14}, {8,14}}, heavy)
{}
//IBlock::~iBlock(){}

void IBlock::rotate(int direction){
    //will come back to this. brain not in the right place lmao
}

char IBlock::getType() const {
    return 'I';
}

