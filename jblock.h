#ifndef _JBLOCK_
#define _JBLOCK_
#include <string>
#include "block.h"

class JBlock : public Block {
    char type = 'J';
    orientationClass orientation;
    public:
        JBlock(bool isHeavy);
        ~JBlock() = default;
        void rotate(int direction) override;
        char getType() const override;
};

#endif
