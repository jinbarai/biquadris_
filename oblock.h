#ifndef _OBLOCK_
#define _OBLOCK_
#include <string>
#include "block.h"

const int O_BLOCK_WIDTH = 2;
const int O_BLOCK_HEIGHT = 2;


class OBlock : public Block {
    public:
        OBlock(bool isHeavy);
        ~OBlock() = default;
        void printBlock(bool n) override;
};

#endif
