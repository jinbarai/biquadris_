#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <memory>

using namespace std;

class Cell;
//
//int CLOCKWISE = 2;
//int COUNTER_CLOCKWISE = 3;
//int LEFT = -1;
//int RIGHT = 1;

class Block{
    int xPos, yPos, height, width;
    bool heavy;
    vector <unique_ptr <Cell>> blockVector;
    public:
        Block(int height, int width, int x, int y, vector <pair <int, int>> cellCoords, bool isHeavy);
        virtual ~Block() = 0;
        virtual void rotate (int direction) = 0;
        void move (int direction);
        bool isHeavy();
        virtual char getType() const = 0;
};
#endif