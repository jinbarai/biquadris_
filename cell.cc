#include "cell.h"

using namespace std;

Cell::Cell(pair<int, int> coord):
    coords{coord} { }

void Cell::updateBy(int x, int y){
    coords.first += x;
    coords.second += y;
}

void Cell::set(int x, int y){
    coords.first = x;
    coords.second = y;
}

int Cell::getX(){
    return coords.first;
}

int Cell:getY(){
    return coords.second;
}