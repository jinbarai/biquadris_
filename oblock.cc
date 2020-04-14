#include "oblock.h"
#include <vector>
#include <memory>


using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

OBlock::OBlock(bool heavy):
Block(O_BLOCK_HEIGHT, O_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X, BLOCK_SPAWN_Y +1}, 
{BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y + 1}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}}, heavy, 'O', orientationClass::h)
{}

void OBlock::printBlock(bool n) {
    if (n == 0) {
        for (int i = 0; i < 2; ++i) {
            cout << 'O';
        }
        for (int i = 0; i < 9; ++i) {
            cout << ' ';
        }
    } else { 
        for (int i = 0; i < 2; ++i) {
            cout << 'O';
        }
        for (int i = 0; i < 9; ++i) {
            cout << ' ';
        }
    }
}
