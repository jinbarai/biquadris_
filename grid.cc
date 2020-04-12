#include "grid.h"
#include <iostream>
#include "controller.h"
using namespace std;

void Grid::init(Player *p1, Player *p2) {
    delete this->td;
    this->theGridp1.clear();
    this->theGridp2.clear();
    this->p1 = p1;
    this->p2 = p2;
    this->td = new TextDisplay(this->p1, this->p2);
    for (int i = 0; i < 18; ++i) {
        vector<Cell> c;
        this->theGridp1.emplace_back(c);
    for (int k = 0; k < 11; ++k) {
            this->theGridp1.at(i).emplace_back(Cell(i,k,' '));
        }
    }
    for (int i = 0; i < 18; ++i) {
        vector<Cell> c;
        this->theGridp2.emplace_back(c);
        for (int k = 0; k < 11; ++k) {
            this->theGridp2.at(i).emplace_back(Cell(i,k,' '));
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

void Grid::update(string s, Block *b) {
    vector <pair <int, int>> coords = b->getCoords();
    char type = b->getType();
    if (s == "p1") { 
        for (int i = 0; i < 4; ++i) {
            int x = coords.at(i).first;
            int y = coords.at(i).second;
            if (theGridp1.at(y).at(x).getType() != ' ') {
                throw GameOver{State::p1};
            }  else { 
                theGridp1.at(y).at(x).setType(type);
                this->td->notify("p1", y, x, type);
            }
        }
    } else { 
        for (int i = 0; i < 4; ++i) {
            int x = coords.at(i).first;
            int y = coords.at(i).second;
            if (theGridp2.at(y).at(x).getType() != ' ') {
                throw GameOver{State::p2};
            }  else { 
                theGridp2.at(y).at(x).setType(type);
                this->td->notify("p2", y, x, type);
            }
        }
    }
}

// moves left & right 
bool Grid::move(State p, Block *b, int dir) { 
    // block and dir come from controller
    vector <pair<int, int>> coords = b->getCoords();
    b->move(dir);
    vector <pair<int, int>> newcoords = b->getCoords();
    if (p == State::p1) { 
        for (int i = 0; i < 4; ++i) {
            int x = newcoords.at(i).first;
            int y = newcoords.at(i).second;
            if (x > 10 || x < 0) {
                b->setCoords(coords);
                return false;
            } if (this->theGridp1.at(y).at(x).getType() != ' ') { 
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
        int x1 = newcoords.at(i).first;
        int y1 = newcoords.at(i).second;
        int oldx = coords.at(i).first;
        int oldy = coords.at(i).second;
        this->theGridp1.at(oldy).at(oldx).setType(' ');
        this->theGridp1.at(y1).at(x1).setType(b->getType());
        this->td->notify("p1", y1, x1, b->getType());
        bool flag = true;
        for (int k = 0; k < 4; ++k) { 
              if (oldx == newcoords.at(k).first && oldy == newcoords.at(k).second) {
                  flag = false;
              } 
        } if (flag == true) { 
            this->td->notify("p1", oldy, oldx, ' ');
        }
    }
     cout << *this;
     return true;
    } else { 
        for (int i = 0; i < 4; ++i) {
        int x = newcoords.at(i).first;
        int y = newcoords.at(i).second;
        if (x > 10 || x < 0) {
            b->setCoords(coords);
            return false;
        } if (this->theGridp2.at(y).at(x).getType() != ' ') { 
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
    } for (int i = 0; i < 4; ++i) {
        int x1 = newcoords.at(i).first;
        int y1 = newcoords.at(i).second;
        int oldx = coords.at(i).first;
        int oldy = coords.at(i).second;
        this->theGridp2.at(oldy).at(oldx).setType(' ');
        this->theGridp2.at(y1).at(x1).setType(b->getType());
        this->td->notify("p2", y1, x1, b->getType());
        bool flag = true;
        for (int k = 0; k < 4; ++k) { 
              if (oldx == newcoords.at(k).first && oldy == newcoords.at(k).second) {
                  flag = false;
              } 
        } if (flag == true) { 
            this->td->notify("p1", oldy, oldx, ' ');
        } 
    }
        cout << *this;
        return true;
    }
}

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
        for (int i = 0; i < 18; ++i) { 
            if (isRowFull(i, s) == false) {
                return false;
            }
        } return true;
    } else { 
        for (int i = 0; i < 18; ++i) { 
            if (isRowFull(i, "p2") == false) {
                return false;
            }
        } return true;
    }
}


void Grid::score(string s, int n, int level) { 
    int score = 1 * level;
    for (int i = 0; i < n; ++i) {
        score *= 10;
    }
    this->getPlayer(s)->addScore(score);
}

void Grid::clear(string s) {
    int level;
    int n = 0;
    level = this->getPlayer(s)->getLevel();
    if (s == "p1") { 
        for (int i = 0; i < 18; ++i) {
            if (isRowFull(i, s)) { 
                ++n;
                for (int k = i + 1; k < 18; ++k) {
                    for (int j = 0; j < 11; ++j) {
                        
                    }
                }
            }
        }
    }
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

