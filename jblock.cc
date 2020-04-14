#include "jblock.h"
#include <vector>
#include <memory>

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

JBlock::JBlock(bool heavy):
Block(J_BLOCK_HEIGHT, J_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y+1}, {BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, 
{BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y}}, heavy, 'J', orientationClass::h)
{}

void JBlock::printBlock(bool n) {
    if (n == 0) {
        cout << 'J';
        for (int i = 0; i < 10; ++i) {
            cout << ' ';
        } 
    } else { 
        for (int i = 0; i < 3; ++i) {
            cout << 'J';
        }
        for (int k = 0; k < 8; ++k) {
            cout << ' ';
        }
    }
}
