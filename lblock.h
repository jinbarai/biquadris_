#ifndef _LBLOCK_
#define _LBLOCK_
#include <string>
#include "block.h"

class LBlock : public Block {
    public:
        LBlock(bool isHeavy);
        ~LBlock() = default;
};

#endif
