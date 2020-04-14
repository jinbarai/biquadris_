#ifndef _TBLOCK_
#define _TBLOCK_
#include <string>
#include "block.h"

class TBlock : public Block {
    public:
        TBlock(bool isHeavy);
        ~TBlock() = default;
        void printBlock(bool n) override;
};

#endif
