#include "block.h"
#include "cell.h"
#include <vector>
#include <memory>
#include <string>
#include <algorithm> // std::reverse
using namespace std;

Block::Block(int h, int w, int x, int y, vector<pair<int, int>> coords, bool isHeavy, char c, orientationClass o): 
height{h}, width{w}, xPos{x}, yPos{y}, coords{coords}, levelHeavy{isHeavy}, type{c}, orient{o}{
    for (int i = 0; i <4; i++){
        this->blockVector.emplace_back(make_unique<Cell> (coords.at(i).first, coords.at(i).second, c));
    }
}

void Block::move(int direction){
    if (direction != DOWN) { 
        for (int i = 0; i < 4; ++i) { 
            this->blockVector.at(i)->updateBy(direction, 0);
            this->coords.at(i).first += direction;
        }
    }  else { //DOWN
        for (int i = 0; i < 4; ++i) { 
            this->blockVector.at(i)->updateBy(0, -1);
            this->coords.at(i).second += -1;
        }
    }
   // vector <pair <int, int>> c = this->getCoords();
    //for (int i = 0; i < 4; i++){
    //    cout << this->coords.at(i).first <<", " << this->coords.at(i).second << endl;
    //    cout << c.at(i).first <<", " << c.at(i).second << endl;
   // }
}


vector<pair<int, int>> Block::getCoords(){
    vector <pair<int, int>> coords;
    for (int i = 0; i < 4; i++){
        coords.emplace_back(make_pair(blockVector.at(i)->getX(), blockVector.at(i)->getY()));
    }
    return coords;
}

static vector <pair <int, int>> rotateCoordsCW(vector <pair <int, int>> coords){
    vector <pair <int, int>> newCoords;
    for (int i = 0; i < 4; i++){
        newCoords.emplace_back(make_pair(coords.at(i).second, -1*coords.at(i).first));
    }
    return newCoords;
}


vector<pair<int, int>> Block::rotate(){
    vector<pair<int, int>> coords;
    vector<pair<int, int>> oldCoords = this->coords;

    int xBottomLeft = this->getBottomX();
    int yBottomLeft = this->getBottomY();
    //translate block such that bottom left of block is (1,1)
    for (int i = 3 ; i >= 0; --i){
        oldCoords.at(i).first =  oldCoords.at(i).first - xBottomLeft + 1;
        oldCoords.at(i).second = oldCoords.at(i).second - yBottomLeft + 1;
    }
    //rotate over Origin (0,0)
    coords = rotateCoordsCW(oldCoords);
 
    //translate Block back to the position it was took from
    for (int i = 0 ; i< 4; ++i){
        if (this->orient == orientationClass::h){
            coords.at(i).second = coords.at(i).second + this->width + 1;
        } else if (this->orient == orientationClass::v){
            coords.at(i).second = coords.at(i).second + this->height + 1;
        }
        coords.at(i).first = coords.at(i).first + xBottomLeft - 1;
        coords.at(i).second = coords.at(i).second + yBottomLeft - 1;
    }
    return coords;
}

void Block::setCoords(vector <pair <int, int>> coords){
    this->coords = coords;
    for (int i = 0; i < 4; ++i){
        this->blockVector[i]->set(coords[i].first, coords[i].second);
    }
}

void Block::switchOrientation() {
    if (this->orient == orientationClass::h) {
        this->orient = orientationClass::v;
        return;
    }
    this->orient = orientationClass::h;
}

char Block::getType() {
    return this->type;
}

bool Block::isLevelHeavy(){
    return this->levelHeavy;
}

void Block::makeLevelHeavy(bool n){
    this->levelHeavy = n;
}

bool Block::isCommandHeavy(){
    return this->commandHeavy;
}

void Block::makeCommandHeavy(bool n){
    this->commandHeavy = n;
}

int Block::getBottomX() { 
    int xBottomLeft = this->coords.at(0).first;
    for (int i = 0; i < 4; i++){
        if (this->coords.at(i).first < xBottomLeft) xBottomLeft = this->coords.at(i).first;
    } 
    return xBottomLeft;
}

int Block::getBottomY() { 
    int yBottomLeft  = this->coords.at(0).second;
    for (int i = 0; i < 4; i++){
        if (this->coords.at(i).second < yBottomLeft) yBottomLeft = this->coords.at(i).second;
    } 
    return yBottomLeft;
}

Block::~Block() {}

