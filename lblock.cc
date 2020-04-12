#include "lblock.h"
#include <vector>
#include <memory>

const int L_BLOCK_WIDTH = 4;
const int L_BLOCK_HEIGHT = 2;

using namespace std;

//intializing learned from https://www.geeksforgeeks.org/multiple-inheritance-in-c/

LBlock::LBlock(bool heavy):
Block(L_BLOCK_HEIGHT, L_BLOCK_WIDTH, BLOCK_SPAWN_X, BLOCK_SPAWN_Y, 
{{BLOCK_SPAWN_X, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X + 1, BLOCK_SPAWN_Y}, 
{BLOCK_SPAWN_X + 2, BLOCK_SPAWN_Y}, {BLOCK_SPAWN_X, BLOCK_SPAWN_Y + 1}}, heavy, 'L', orientationClass::h)
{}
