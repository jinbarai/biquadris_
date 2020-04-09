#ifndef CELL_H
#define CELL_H

class Cell{
    int x; 
    int y;
    public:
        Cell(int x, int y);
        bool isEmpty = false;
        void updateBy(int x, int y);
        void set(int x, int y);
        int getX();
        int getY();
};
#endif
