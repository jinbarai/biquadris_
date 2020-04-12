#include "block.h"
#include "cell.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

using namespace std;

Block::Block(int h, int w, int x, int y, vector<pair<int, int>> coords, bool isHeavy, char c, orientationClass o): 
height{h}, width{w}, xPos{x}, yPos{y}, heavy{isHeavy}, coords{coords}, type{c}, orient{o}{
    this->blockVector.emplace_back(make_unique<Cell> (coords.at(0).first, coords.at(0).second, c));
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

static vector <pair <int, int>> rotateCoordsCW(vector <pair <int, int>> coords){
    vector <pair <int, int>> newCoords;
    for (int i = 0; i < 4; i++){
        newCoords.emplace_back(make_pair(coords.at(i).second, -1*coords.at(i).first));
    }
    return newCoords;
}

static vector <pair <int, int>> rotateCoordsCCW(vector <pair <int, int>> coords){
    vector <pair <int, int>> newCoords;
    for (int i = 0; i < 4; i++){
        newCoords.emplace_back(make_pair(-1*coords.at(i).second, coords.at(i).first));
    }
    return newCoords;
}

vector<pair<int, int>> Block::rotate(int direction){
    vector<pair<int, int>> coords;
    vector<pair<int, int>> oldCoords = this->coords;
    for (int i = 0 ; i < 4; ++i){
        oldCoords.at(i).first =  oldCoords.at(i).first - this->xPos + 1;
        oldCoords.at(i).second = oldCoords.at(i).second - this->yPos + 1;
    }
    if (direction == CLOCKWISE){
        coords = rotateCoordsCW(oldCoords);
    }
    else if (direction == COUNTER_CLOCKWISE){
        coords = rotateCoordsCCW(oldCoords);
    }

    for (int i = 0 ; i< 4; ++i){
        if (this->orient == orientationClass::v){
            coords.at(i).second = coords.at(i).second + this->yPos + this->width;
        } else if (this->orient == orientationClass::h){
            coords.at(i).second = coords.at(i).second + this->yPos + this->height;
        }   
    }
    return coords;
}

void Block::setCoords(vector <pair <int, int>> coords){
    this->coords = coords;
    for (int i = 0; i < 4; ++i){
        this->blockVector[i]->set(coords[i].first, coords[i].second);
    }
}

void Block::setOrientation(orientationClass o){
    this->orient = o;
}

char Block::getType() {
    return this->type;
}


bool Block::isHeavy(){
    return this->heavy;
}

//pair <int, int> Block::getPos(){
//    pair <int, int> pos = make_pair(this->xPos, this->yPos);
//    return pos;
//}

Block::~Block() {}

