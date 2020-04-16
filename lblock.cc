#include "lblock.h"
#include <vector>
#include <memory>

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

LBlock::LBlock(bool heavy):
Block(L_BLOCK_HEIGHT, L_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}, 
{BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y + 1}}, heavy, 'L', orientationClass::h)
{}


void LBlock::printBlock(bool n) {
    if (n == 0) {
        for (int i = 0; i < 2; ++i) {
            cout << ' ';
        }
        cout << 'L';
        for (int i = 0; i < 8; ++i) {
            cout << ' ';
        }
    } else { 
        for (int i = 0; i < 3; ++i) {
            cout << 'L';
        }
        for (int i = 0; i < 8; ++i) {
            cout << ' ';
        }
    }
}
