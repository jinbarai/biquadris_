#include "block.h"
#include "cell.h"
#include <vector>
#include <memory>
#include <string>

using namespace std;

Block::Block(int h, int w, int x, int y, vector<pair<int, int>> coords, bool isHeavy):
height{h}, width{w}, xPos{x}, yPos{y}, heavy{isHeavy}{
    this->blockVector.emplace_back(new Cell (coords[0].first, coords[0].second));
    this->blockVector.emplace_back(new Cell (coords[1].first, coords[1].second));
    this->blockVector.emplace_back(new Cell (coords[2].first, coords[2].second));
    this->blockVector.emplace_back(new Cell (coords[3].first, coords[3].second));
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

Block::~Block() {}

