#include "zblock.h"
#include <vector>
#include <memory>

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

ZBlock::ZBlock(bool heavy):
Block(Z_BLOCK_HEIGHT, Z_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y+1}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y +1}, 
{BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y}}, heavy, 'Z', orientationClass::h)
{}

void ZBlock::printBlock(bool n) {
    if (n == 0) {
        for (int i = 0; i < 2; ++i) {
            cout << 'Z';
        }
        for (int i = 0; i < 9; ++i) {
            cout << ' ';
        }
    } else { 
        cout << ' ';
        for (int i = 0; i < 2; ++i) {
            cout << 'Z';
        }
        for (int i = 0; i < 8; ++i) {
            cout << ' ';
        }
    }
}
