#ifndef _LBLOCK_
#define _LBLOCK_
#include <string>
#include "block.h"

const int L_BLOCK_WIDTH = 3;
const int L_BLOCK_HEIGHT = 2;

class LBlock : public Block {
    public:
        LBlock(bool isHeavy);
        ~LBlock() = default;
        void printBlock(bool n) override;
};

#endif
