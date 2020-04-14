#ifndef _SBLOCK_
#define _SBLOCK_
#include <string>
#include "block.h"

const int S_BLOCK_WIDTH = 3;
const int S_BLOCK_HEIGHT = 2;


class SBlock : public Block {
    public:
        SBlock(bool isHeavy);
        ~SBlock() = default;
        void printBlock(bool n) override;
};

#endif
