#ifndef _SBLOCK_
#define _SBLOCK_
#include <string>
#include "block.h"

class SBlock : public Block {
    char type = 'S';
    public:
        SBlock(bool isHeavy);
        ~SBlock() = default;
};

#endif
