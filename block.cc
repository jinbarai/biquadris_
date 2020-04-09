#include "block.h"
#include "cell.h"
#include <vector>
#include <memory>

using namespace std;

Block::Block(int h, int w, int x, int y, vector<pair<int, int>> coords, bool isHeavy):
height{h}, width{w}, xPos{x}, yPos{y}, heavy{isHeavy}{
    this->blockVector.emplace_back(make_unique<Cell> (coords[0]));
    this->blockVector.emplace_back(make_unique<Cell> (coords[1]));
    this->blockVector.emplace_back(make_unique<Cell> (coords[2]));
    this->blockVector.emplace_back(make_unique<Cell> (coords[3]));
}

//Block::~Block(){}
void Block::rotate (int direction) {}

void Block::move(int direction){
    for (auto &cell: this->blockVector){
        cell.updateBy(direction, 0);
        if (this->heavy) cell.updateBy(0, 1);
    }
}

bool Block::isHeavy(){
    return this->heavy;
}

 char getType (){}

