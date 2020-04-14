#ifndef _TBLOCK_
#define _TBLOCK_
#include <string>
#include "block.h"

const int T_BLOCK_WIDTH = 3;
const int T_BLOCK_HEIGHT = 2;

class TBlock : public Block {
    public:
        TBlock(bool isHeavy);
        ~TBlock() = default;
        void printBlock(bool n) override;
};

#endif
