#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <memory>

using namespace std;

class Cell;
enum class orientationClass { v , h };

const int CLOCKWISE = 2;
const int COUNTER_CLOCKWISE = 3;
const int LEFT = -1;
const int RIGHT = 1;

const int BLOCK_SPAWN_X = 0;
const int BLOCK_SPAWN_Y = 14;

class Block{
    int xPos, yPos, height, width;
    char type;
    bool heavy;
    vector <unique_ptr <Cell>> blockVector;
    vector < pair<int, int>> coords;
    public:
        Block(int height, int width, int x, int y, vector <pair <int, int>> cellCoords, bool isHeavy, char type);
        virtual ~Block() = 0;
        virtual void rotate (int direction) = 0;
        void move (int direction);
        vector <pair <int, int>> getCoords();
        void setCoords(vector <pair <int, int>> coords);
        bool isHeavy();
        char getType();
};
#endif
