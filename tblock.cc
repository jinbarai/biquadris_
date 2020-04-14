#include "tblock.h"
#include <vector>
#include <memory>

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

TBlock::TBlock(bool heavy):
Block(T_BLOCK_HEIGHT, T_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y+1}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y +1}, 
{BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y+1}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}}, heavy, 'T', orientationClass::h)
{}

void TBlock::printBlock(bool n) {
    if (n == 0) {
        for (int i = 0; i < 3; ++i) {
            cout << 'T';
        }
        for (int i = 0; i < 8; ++i) {
            cout << ' ';
        }
    } else { 
        cout << ' ';
        cout << 'T';
        for (int i = 0; i < 9; ++i) {
            cout << ' ';
        }
    }
}

