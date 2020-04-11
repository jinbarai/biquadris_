#include "iblock.h"
#include <vector>
#include <memory>
#include <iostream>

const int I_BLOCK_WIDTH = 1;
const int I_BLOCK_HEIGHT = 4;


using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

IBlock::IBlock(bool heavy):
Block(I_BLOCK_HEIGHT, I_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X,BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X,BLOCK_SPAWN_Y+1}, 
{BLOCK_SPAWN_X,BLOCK_SPAWN_Y+2}, {BLOCK_SPAWN_X,BLOCK_SPAWN_Y+3}}, 'I', heavy)
{
    this->orientation = orientationClass::v;
}



void IBlock::rotate(int direction){
    vector<pair<int, int>> coords;
    vector<pair<int, int>> oldCoords = this->getCoords();
    bool possible = true;
    if (this->orientation == orientationClass::v){
        for (int i = 0; i < 4; ++i){
            int x = oldCoords[0].first + i;
            int y = oldCoords[0].second;
            coords.emplace_back(make_pair(x, y));
            if (x > 11) possible = false;
        }
        if (possible) this->orientation = orientationClass::h;
    } else {
        for (int i = 0; i < 4; ++i){
            int x = oldCoords[0].first;
            int y = oldCoords[0].second+i;
            coords.emplace_back(make_pair(x, y));
        }
    }
    if (!possible) coords = oldCoords;
    
    this->setCoords(coords);
}

char IBlock::getType() const {
    return this->type;
}

