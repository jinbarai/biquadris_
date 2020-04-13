#ifndef _ZBLOCK_
#define _ZBLOCK_
#include <string>
#include "block.h"

class ZBlock : public Block {
    public:
        ZBlock(bool isHeavy);
        ~ZBlock() = default;
};

#endif
