#include "tblock.h"
#include <vector>
#include <memory>

const int T_BLOCK_WIDTH = 3;
const int T_BLOCK_HEIGHT = 2;

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

TBlock::TBlock(bool heavy):
Block(T_BLOCK_HEIGHT, T_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y+1}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y +1}, 
{BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y+1}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}}, heavy, 'T', orientationClass::h)
{}
