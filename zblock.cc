#include "zblock.h"
#include <vector>
#include <memory>

const int Z_BLOCK_WIDTH = 3;
const int Z_BLOCK_HEIGHT = 2;

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

ZBlock::ZBlock(bool heavy):
Block(Z_BLOCK_HEIGHT, Z_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y+1}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y +1}, 
{BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y}}, heavy, 'Z', orientationClass::h)
{}
