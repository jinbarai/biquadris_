#ifndef _SBLOCK_
#define _SBLOCK_
#include <string>
#include "block.h"

class SBlock : public Block {
    public:
        SBlock(bool isHeavy);
        ~SBlock() = default;
        void printBlock(bool n) override;
};

#endif
