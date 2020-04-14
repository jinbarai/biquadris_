#ifndef _OBLOCK_
#define _OBLOCK_
#include <string>
#include "block.h"

class OBlock : public Block {
    public:
        OBlock(bool isHeavy);
        ~OBlock() = default;
        void printBlock(bool n) override;
};

#endif
