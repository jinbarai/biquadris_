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
{BLOCK_SPAWN_X,BLOCK_SPAWN_Y+2}, {BLOCK_SPAWN_X,BLOCK_SPAWN_Y+3}}, heavy, 'I', orientationClass::h)
{}

void IBlock::printBlock(bool n) {
    if (n == 0) {
        for (int k = 0; k < 4; ++k) {
            cout << 'I';
        }
        for (int i = 0; i < 7; ++i) {
            cout << ' ';
        }
    } else { 
        for (int i = 0; i < 11; ++i) {
            cout << ' ';
        }
    }
}