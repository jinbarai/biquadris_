#include "sblock.h"
#include <vector>
#include <memory>

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

SBlock::SBlock(bool heavy):
Block(S_BLOCK_HEIGHT, S_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}, 
{BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y + 1}, {BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y + 1}}, heavy, 'S', orientationClass::h)
{}

void SBlock::printBlock(bool n) {
    if (n == 0) {
        cout << ' ';
        for (int i = 0; i < 2; ++i) {
            cout << 'S';
        }
        for (int i = 0; i < 8; ++i) {
            cout << ' ';
        }
    } else { 
        for (int i = 0; i < 2; ++i) {
            cout << 'S';
        }
        for (int i = 0; i < 9; ++i) {
            cout << ' ';
        }
    }
}

