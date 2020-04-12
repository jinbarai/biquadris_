#include "sblock.h"
#include <vector>
#include <memory>

const int S_BLOCK_WIDTH = 3;
const int S_BLOCK_HEIGHT = 2;

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

SBlock::SBlock(bool heavy):
Block(S_BLOCK_HEIGHT, S_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}, 
{BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y + 1}, {BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y + 1}}, heavy, 'S', orientationClass::h)
{}
