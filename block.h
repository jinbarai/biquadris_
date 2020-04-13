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
const int DOWN = 5;

const int BLOCK_SPAWN_X = 0;
const int BLOCK_SPAWN_Y = 14;

class Block{
    vector <unique_ptr <Cell>> blockVector;    
    int height, width, xPos, yPos;
    vector < pair<int, int>> coords;
    bool heavy; 
    char type;
    orientationClass orient;
    public:
        Block(int height, int width, int x, int y, vector <pair <int, int>> cellCoords, 
              bool isHeavy, char type, orientationClass orient);
        virtual ~Block() = 0;
        vector < pair<int, int>> rotate (int direction);
        void move (int direction);
        vector <pair <int, int>> getCoords();
        void setCoords(vector <pair <int, int>> coords);
        pair <int, int> getPos();
        bool isHeavy();
        void setOrientation(orientationClass);
        char getType();
};
#endif
