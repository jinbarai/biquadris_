#include "iblock.h"
#include <vector>
#include <memory>

extern const int I_BLOCK_WIDTH = 1;
extern const int I_BLOCK_HEIGHT = 4;
extern const int I_BLOCK_SPAWN_X = 6;
extern const int I_BLOCK_SPAWN_Y = 2;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

IBlock::IBlock(int h, int w, int x, int y, vector<pair<int, int>> coords, bool isHeavy):
height{h}, width{w}, xPos{x}, yPos{y}, heavy{isHeavy}{
    this->blockVector.emplace_back(make_unique<Cell> (coords[0].first, coords[0].second));
    this->blockVector.emplace_back(make_unique<Cell> (coords[1].first, coords[1].second));
    this->blockVector.emplace_back(make_unique<Cell> (coords[2].first, coords[2].second));
    this->blockVector.emplace_back(make_unique<Cell> (coords[3].first, coords[3].second));
}

void Block::move(int direction){
    for (auto &cell: this->blockVector){
        cell->updateBy(direction, 0);
        if (this->heavy) cell->updateBy(0, 1);
    }
}

bool Block::isHeavy(){
    return this->heavy;
}
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

