#ifndef CELL_H
#define CELL_H

class Cell{
    int x; 
    int y;
    char type;
    public:
        Cell(int x, int y, char c);
        bool isEmpty();
        void updateBy(int x, int y);
        void set(int x, int y);
        int getX();
        int getY();
        char getType();
        void setType(char c);
};

#endif
