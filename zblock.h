#ifndef _ZBLOCK_
#define _ZBLOCK_
#include <string>
#include "block.h"

const int Z_BLOCK_WIDTH = 3;
const int Z_BLOCK_HEIGHT = 2;

class ZBlock : public Block {
    public:
        ZBlock(bool isHeavy);
        ~ZBlock() = default;
        void printBlock(bool n) override;
};

#endif
