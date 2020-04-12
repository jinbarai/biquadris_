#ifndef _JBLOCK_
#define _JBLOCK_
#include <string>
#include "block.h"

class JBlock : public Block {
    char type = 'J';
    public:
        JBlock(bool isHeavy);
        ~JBlock() = default;
};

#endif
