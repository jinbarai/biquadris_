#ifndef CELL_H
#define CELL_H
using namespace std;
class Cell{
    pair <int, int> coords;
    
    public:
        Cell(pair <int, int> coord);

        void updateBy(int x, int y);
        void set(int x, int y);
        int getX();
        int getY();
};
#endif