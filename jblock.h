#ifndef _JBLOCK_
#define _JBLOCK_
#include <string>
#include "block.h"

const int J_BLOCK_WIDTH = 3;
const int J_BLOCK_HEIGHT = 2;


class JBlock : public Block {
    public:
        JBlock(bool isHeavy);
        ~JBlock() = default;
        void printBlock(bool n) override;
};

#endif
