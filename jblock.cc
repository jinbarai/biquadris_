#include "jblock.h"
#include <vector>
#include <memory>
#include <iostream>

const int J_BLOCK_WIDTH = 4;
const int J_BLOCK_HEIGHT = 2;

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

JBLOCK::JBLOCK(bool heavy):
Block(J_BLOCK_HEIGHT, J_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X, BLOCK_SPAWN_Y+1}, 
{BLOCK_SPAWN_X, BLOCK_SPAWN_Y+2}, {BLOCK_SPAWN_X, BLOCK_SPAWN_Y+3}}, heavy)
{
    this->orientation = orientationClass::v;
}



void JBLOCK::rotate(int direction){
    vector<pair<int, int>> coords;
    vector<pair<int, int>> oldCoords = this->getCoords();
    bool possible = true;
    if (this->orientation == orientationClass::v){
        //
        if (possible) this->orientation = orientationClass::h;
    } else {
        //
    }
    if (!possible) coords = oldCoords;
    
    this->setCoords(coords);
}

char JBLOCK::getType() const {
    return this->type;
}

