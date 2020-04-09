#ifndef _IBLOCK_
#define _IBLOCK_
#include <string>
#include "block.h"

class IBlock : public Block {
    public:
        IBlock(int h, int w, int x, int y, vector<pair<int, int>> coords, bool isHeavy);
        ~IBlock();
        void rotate(int direction) override;
        char getType() const override;
};

#endif
