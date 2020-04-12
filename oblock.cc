#include "oblock.h"
#include <vector>
#include <memory>

const int O_BLOCK_WIDTH = 2;
const int O_BLOCK_HEIGHT = 2;

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

OBlock::OBlock(bool heavy):
Block(O_BLOCK_HEIGHT, O_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X, BLOCK_SPAWN_Y +1}, 
{BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y + 1}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}}, heavy, 'O', orientationClass::h)
{}
