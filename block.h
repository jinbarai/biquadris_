#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <memory>
#include <iostream>

class Cell;
enum class orientationClass { v , h };

const int CLOCKWISE = 2;
const int LEFT = -1;
const int RIGHT = 1;
const int DOWN = 5;

const int BLOCK_SPAWN_X = 0;
const int BLOCK_SPAWN_Y = 14;

class Block{
    std::vector <std::unique_ptr <Cell>> blockVector;    
    int height, width, xPos, yPos;
    std::vector < std::pair<int, int>> coords;
    bool levelHeavy; 
    bool commandHeavy = false;
    char type;
    orientationClass orient;
    public:
        Block(int height, int width, int x, int y, std::vector <std::pair <int, int>> cellCoords, 
              bool isHeavy, char type, orientationClass orient);
        virtual ~Block() = 0;
        std::vector < std::pair<int, int>> rotate ();
        void move (int direction);
        std::vector <std::pair <int, int>> getCoords();
        void setCoords(std::vector <std::pair <int, int>> coords);
        std::pair <int, int> getPos();
        bool isLevelHeavy();
        void dropByOne();
        void makeLevelHeavy(bool n);
        bool isCommandHeavy();
        void makeCommandHeavy(bool n);
        void switchOrientation();
        char getType();
        int getBottomX();
        int getBottomY();
        virtual void printBlock(bool n) = 0; 
};
#endif
