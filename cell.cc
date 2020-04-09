#include "cell.h"
using namespace std;

Cell::Cell(int x, int y) : x{x}, y{y} {}

void Cell::updateBy(int x, int y){
    this->x += x;
    this->y += y;
}

void Cell::set(int x, int y){
    this->x = x;
    this->y = y;
}

int Cell::getX(){
    return this->x;
}

int Cell::getY(){
    return this->y;
}
