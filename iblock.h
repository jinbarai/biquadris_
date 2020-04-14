#ifndef _IBLOCK_
#define _IBLOCK_
#include <string>
#include "block.h"

const int I_BLOCK_WIDTH = 1;
const int I_BLOCK_HEIGHT = 4;

class IBlock : public Block {
    public:
        IBlock(bool isHeavy);
        void printBlock(bool n) override;
        ~IBlock() = default;
};

#endif

