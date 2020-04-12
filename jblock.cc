#include "jblock.h"
#include <vector>
#include <memory>

const int J_BLOCK_WIDTH = 4;
const int J_BLOCK_HEIGHT = 2;

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

JBlock::JBlock(bool heavy):
Block(J_BLOCK_HEIGHT, J_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y+1}, {BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, 
{BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y}}, heavy, 'J', orientationClass::h)
{}
