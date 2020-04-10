#ifndef _IBLOCK_
#define _IBLOCK_
#include <string>
#include "block.h"

class IBlock : public Block {
    public:
        IBlock(bool isHeavy);
        ~IBlock() = default;
        void rotate(int direction) override;
        char getType() const override;
};

#endif
