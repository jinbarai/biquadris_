#include "grid.h"
#include <iostream>
#include "levels.h"
using namespace std;

void Grid::init(Player *p1, Player *p2) {
    this->p1 = p1;
    this->p2 =p2;
    this->td = new TextDisplay(this->p1, this->p2);
    for (int i = 0; i < 15; ++i) {
        vector<Cell> c;
        this->theGridp1.emplace_back(c);
        for (int k = 0; k < 11; ++k) {
            this->theGridp1.at(i).emplace_back(Cell(i,k));
        }
    }
    for (int i = 0; i < 15; ++i) {
        vector<Cell> c;
        this->theGridp2.emplace_back(c);
        for (int k = 0; k < 11; ++k) {
            this->theGridp2.at(i).emplace_back(Cell(i,k));
        }
    }
    cout << *this;
}
/*
void Grid::changeLevel(int n, string s) {
    Player *p;
    if (s == "p1") {
        p =  this->p1;
    } else { 
        p = this->p2;
    }
    if (n == 0) {
        p->changeLevel(new levelzero, 0); // add notes based on level code
    } else if (n == 1) {
        p->changeLevel(new levelone, 1); 
    } else if (n == 2) {
        p->changeLevel(new leveltwo, 2);
    } else if (n == 3) {
        p->changeLevel(new levelthree, 3);
    } else if (n == 4) {
        p->changeLevel(new levelfour, 4);
    } /*else if (n == 5) {
        this->level = new Level5(); 
    } else if (n == 6) {
       this->level = new Level6();
    } 
}
*/

bool Grid::isRowFull(int n, string s) { 
    if (s == "p1") { 
        for (int i = 0; i < 11; ++i) {
            if (this->theGridp1.at(n).at(i).isEmpty == true) {
                return false;
            }
        } return true;
    } else { 
        for (int i = 0; i < 11; ++i) {
            if (this->theGridp2.at(n).at(i).isEmpty == true) {
                return false;
            }
        } return true;
    }
}

bool Grid::isFull(string s) { 
    if  (s == "p1") { 
        for (int i = 0; i < 15; ++i) { 
            if (isRowFull(i, s) == false) {
                return false;
            }
        } return true;
    } else { 
        for (int i = 0; i < 15; ++i) { 
            if (isRowFull(i, "p2") == false) {
                return false;
            }
        } return true;
    }
}

void Grid::clear() {
// add a lot of code
}

Player *Grid::getPlayer(string s) {
    if (s == "p1") { 
        return this->p1;
    }
    else return this->p2;
}

ostream &operator<<(ostream &out, const Grid &gr) { 
    out << *gr.td;
    return out;
}

Grid::~Grid() { 
    delete this->p1;
    delete this->p2;
    delete this->td;
}

