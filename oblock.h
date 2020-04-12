#ifndef _OBLOCK_
#define _OBLOCK_
#include <string>
#include "block.h"

class OBlock : public Block {
    char type = 'O';
    public:
        OBlock(bool isHeavy);
        ~OBlock() = default;
};

#endif
