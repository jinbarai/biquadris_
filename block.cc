#include "block.h"
#include "cell.h"
#include <vector>
#include <memory>
#include <string>

using namespace std;

Block::Block(int h, int w, int x, int y, vector<pair<int, int>> coords, bool isHeavy, char c):
height{h}, width{w}, xPos{x}, yPos{y}, heavy{isHeavy}, coords{coords}, type{c}{
    this->blockVector.emplace_back(make_unique<Cell> (coords[0].first, coords[0].second, c));
    this->blockVector.emplace_back(make_unique<Cell> (coords[1].first, coords[1].second, c));
    this->blockVector.emplace_back(make_unique<Cell> (coords[2].first, coords[2].second, c));
    this->blockVector.emplace_back(make_unique<Cell> (coords[3].first, coords[3].second, c));
}

void Block::move(int direction){
    for (auto &cell: this->blockVector){
        cell->updateBy(direction, 0);
        if (this->heavy) cell->updateBy(0, 1);
    }
}

vector<pair<int, int>> Block::getCoords(){
    return this->coords;
}

void Block::setCoords(vector <pair <int, int>> coords){
    for (int i = 0; i < 4; ++i){
        this->blockVector[i]->set(coords[i].first, coords[i].second);
    }
}


bool Block::isHeavy(){
    return this->heavy;
}

Block::~Block() {}

