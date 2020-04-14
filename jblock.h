#ifndef _JBLOCK_
#define _JBLOCK_
#include <string>
#include "block.h"

class JBlock : public Block {
    public:
        JBlock(bool isHeavy);
        ~JBlock() = default;
        void printBlock(bool n) override;
};

#endif
