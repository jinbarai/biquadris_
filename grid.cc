#include "grid.h"
#include <iostream>
using namespace std;

Grid::Grid(Player *p) {
    delete this->td;
    this->theGrid.clear();
    this->p = p;
    for (int i = 0; i < 18; ++i) {
        vector<Cell> c;
        this->theGrid.emplace_back(c);
        for (int k = 0; k < 11; ++k) {
            this->theGrid.at(i).emplace_back(Cell(i,k,' '));
        }
    }
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
    } else if (n == 5) {
        this->level = new Level5(); 
    } else if (n == 6) {
       this->level = new Level6();
    } 
}
*/

void Grid::update(State p) {
    Block *b = this->getPlayer()->getBlock();
    vector <pair <int, int>> coords = b->getCoords();
    char type = b->getType(); 
    for (int i = 0; i < 4; ++i) {
        int x = coords.at(i).first;
        int y = coords.at(i).second;
        if (theGrid.at(y).at(x).getType() != ' ') {
            throw GameOver{p};
        }  else { 
            theGrid.at(y).at(x).setType(type);
            this->td->notify(p, y, x, type);
        }
    }
}

// moves left & right 
bool Grid::move(State p, int dir) { 
    Block *b = this->getPlayer()->getBlock();
    // block and dir come from controller
    vector <pair<int, int>> coords = b->getCoords();
    b->move(dir);
    vector <pair<int, int>> newcoords = b->getCoords();
    for (int i = 0; i < 4; ++i) {
        // check to make sure new coordinatres are valid 
        int x = newcoords.at(i).first;
        int y = newcoords.at(i).second;
        if (!validate(x, y)) {
            b->setCoords(coords);
            return false;
        } 
        if (this->theGrid.at(y).at(x).getType() != ' ') { 
            int flag = 1;
            for (int k = 0; k < 4; ++k) {
                if (x == coords.at(k).first && y == coords.at(k).second) { 
                    flag = 0;
                    break;
                } 
            } if (flag == 1) { 
                b->setCoords(coords);
                return false;
            }
        }
    } 
    for (int i = 0; i < 4; ++i) {
        int oldx = coords.at(i).first;
        int oldy = coords.at(i).second;
        this->clear(p, oldy, oldx);
    }
    for (int k = 0; k < 4; ++k) {
        int x = newcoords.at(k).first;
        int y = newcoords.at(k).second;
        char c = b->getType();
        this->theGrid.at(y).at(x).setType(c);
        this->td->notify(p, y, x, c);
    }
    cout << *this;
    return true;
}

bool Grid::validate(int x, int y)  {
    if (x > 10 || x < 0) {
        return false;
    } else if (y > 17 || y < 0) {
        return false;
    } 
    return true;
}

int Grid::down(State p) {
    Block *b = this->getPlayer()->getBlock();
    vector <pair<int, int>> coords = b->getCoords();
    b->move(DOWN);
    vector <pair<int, int>> newcoords = b->getCoords();
    for (int i = 0; i < 4; ++i) {
        int x = newcoords.at(i).first;
        int y = newcoords.at(i).second;
        if (!validate(x, y)) {
            b->setCoords(coords);
            return false;
        } 
        if (this->theGrid.at(y).at(x).getType() != ' ') { 
            int flag = 1;
            for (int k = 0; k < 4; ++k) {
                if (x == coords.at(k).first && y == coords.at(k).second) { 
                    flag = 0;
                    break;
                } 
            } if (flag == 1) { 
                b->setCoords(coords);
                return false;
            }
        }
    } 
    for (int i = 0; i < 4; ++i) {
        int oldx = coords.at(i).first;
        int oldy = coords.at(i).second;
        this->clear(p, oldy, oldx);
    }
    for (int k = 0; k < 4; ++k) {
        int x = newcoords.at(k).first;
        int y = newcoords.at(k).second;
        char c = b->getType();
        this->theGrid.at(y).at(x).setType(c);
        this->td->notify(p, y, x, c);
    }
    for (int i = 0; i < 4; ++i) {
        int x = newcoords.at(i).first;
        int y = newcoords.at(i).second;
        if (y == 0) {
            return -1;
        } else if (this->theGrid.at(y - 1).at(x).getType() != ' ') {
            bool flag = true;
            for (int k = 0; k < 4; ++k) {
                int newx = newcoords.at(k).first;
                int newy = newcoords.at(k).second;
                if (newx == x && newy == y - 1) { 
                    flag = false;
                    break;
                }
            }
            if (flag == true) {
                return -1;
            }
        }
    }
    return 1;
}

void Grid::drop(State p) {
    int val = 1;
    while (val == 1) {
        val =  this->down(p);
    }
    cout << *this;
}

    /*
    for (int i = 0; i < 4; ++i) {
        int x1 = newcoords.at(i).first;
        int y1 = newcoords.at(i).second;
        int oldx = coords.at(i).first;
        int oldy = coords.at(i).second;
        this->theGrid.at(oldy).at(oldx).setType(' ');
        this->theGrid.at(y1).at(x1).setType(b->getType());
        this->td->notify(p, y1, x1, b->getType());
        bool flag = true;
        for (int k = 0; k < 4; ++k) { 
              if (oldx == newcoords.at(k).first && oldy == newcoords.at(k).second) {
                  flag = false;
              } 
        } if (flag == true) { 
            this->td->notify(p, oldy, oldx, ' ');
        }
    }
     cout << *this;
     return true;
    } 
    */

void Grid::clear(State p, int row, int col) {
    char c = ' ';
    this->theGrid.at(row).at(col).setType(c);
    this->td->notify(p, row, col, c);
}

bool Grid::isRowFull(int n) { 
    for (int i = 0; i < 11; ++i) {
         if (this->theGrid.at(n).at(i).isEmpty == true) {
            return false;
        }
    } 
    return true;
}     

bool Grid::isFull() {  
    for (int i = 0; i < 18; ++i) { 
        if (isRowFull(i) == false) {
            return false;
        }
    } 
    return true;
}


void Grid::score(int n, int level) { 
    int score = 1 * level;
    for (int i = 0; i < n; ++i) {
        score *= 10;
    }
    this->getPlayer()->addScore(score);
}

void Grid::rowclear() {
    int level;
    int n = 0;
    level = this->getPlayer()->getLevel();
    for (int i = 0; i < 18; ++i) {
        if (isRowFull(i)) { 
            ++n;
            for (int k = i + 1; k < 18; ++k) {
                 for (int j = 0; j < 11; ++j) {
                        
                }
            }
        }
    }
}

void Grid::setTD(TextDisplay *td) { 
    this->td = td;
}
                    
Player *Grid::getPlayer() {
    return this->p;
}

ostream &operator<<(ostream &out, const Grid &gr) { 
    out << *gr.td;
    return out;
}

Grid::~Grid() { 
    delete this->p;
    delete this->td;
}

