#include "grid.h"
#include <iostream>
#include "levels.h"
using namespace std;

void Grid::init(int n) {
    if (n == 0) {
        this->level = new levelzero(); // add notes based on level code
    } else if (n == 1) {
        this->level = new levelone(); 
    } else if (n == 2) {
        this->level = new leveltwo(); 
    } else if (n == 3) {
        this->level = new levelthree(); 
    } else if (n == 4) {
        this->level = new levelfour(); 
    } /*else if (n == 5) {
        this->level = new Level5(); 
    } else if (n == 6) {
       this->level = new Level6();
    } */
    this->td = new TextDisplay{this->level};
    for (int i = 0; i < 15; ++i) {
        vector<Cell> c;
        this->theGrid.emplace_back(c);
        for (int k = 0; k < 11; ++k) {
            this->theGrid.at(i).emplace_back(Cell(i,k));
        }
    }
    cout << *this;
}

void Grid::changeLevel(int n) {
    delete this->level;
    if (n == 0) {
        this->level = new levelzero; // add notes based on level code
    } else if (n == 1) {
        this->level = new levelone(); 
    } else if (n == 2) {
        this->level = new leveltwo(); 
    } else if (n == 3) {
        this->level = new levelthree(); 
    } else if (n == 4) {
        this->level = new levelfour(); 
    } /*else if (n == 5) {
        this->level = new Level5(); 
    } else if (n == 6) {
       this->level = new Level6();
    } */
}

bool Grid::isRowFull(int n) { 
    for (int i = 0; i < 11; ++i) {
        if (this->theGrid.at(n).at(i).isEmpty == true) {
            return false;
        }
    } return true;
}

bool Grid::isFull() { 
    for (int i = 0; i < 15; ++i) { 
        if (isRowFull(i) == false) {
            return false;
        }
    } return true;
}

void Grid::clear() {
// add a lot of code
}

ostream &operator<<(ostream &out, const Grid &gr) { 
    out << *gr.td;
    return out;
}

Grid::~Grid() { 
    delete this->level;
    delete this->td;
}
