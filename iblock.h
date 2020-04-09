#ifndef _IBLOCK_
#define _IBLOCK_
class Block;

class IBlock : public Block {
    public:
        IBlock(bool heavy)
      //  ~IBlock() override;
        void rotate(int direction) override;
        string getType() const override;
}

#endif