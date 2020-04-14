#ifndef _IBLOCK_
#define _IBLOCK_
#include <string>
#include "block.h"

class IBlock : public Block {
    public:
        IBlock(bool isHeavy);
        void printBlock(bool n) override;
        ~IBlock() = default;
      //  void rotate(int direction) override;
};

#endif
