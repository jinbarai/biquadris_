#include "cell.h"

Cell::Cell(int x, int y, char c) : x{x}, y{y}, type{c} {}

bool Cell::isEmpty() {
    if (this->type == ' ') return true;
    return false;
}

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

char Cell::getType() {
    return this->type;
}

void Cell::setType(char c) {
    this->type = c;
}

