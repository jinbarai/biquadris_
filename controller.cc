#include "controller.h"

Controller::Controller(Grid *g1, Grid *g2) {
    this->g1 = g1;
    this->g2 = g2;
    this->turn = State::p1;
}

Grid *Controller::getGrid() {
    if  (this->turn == State::p1) {
        return this->g1;
    } else  { 
        return this->g2;
    }
}

void Controller::changeTurn() {
    if (this->turn == State::p1) {
        this->turn = State::p2;
        return;
    } else { 
        this->turn = State::p1;
        return;
    }
}

void Controller::levelup() {
    int level = this->getGrid()->getPlayer()->getLevel();
    ++level;
    this->getGrid()->getPlayer()->changeLevel(level);
}

void Controller::leveldown() {
    int level = this->getGrid()->getPlayer()->getLevel();
    --level;
    this->getGrid()->getPlayer()->changeLevel(level);
}
  
  void Controller::startlevel(int n) { 
      this->getGrid()->getPlayer()->changeLevel(n);
      this->getGrid()->getPlayer()->changeLevel(n);
  }

// called to move a block right 
void Controller::move(int n, int dir) { 
    for (int i = 0; i < n; ++i) {
        this->getGrid()->move(this->turn, dir);
    }
}

// Need this for norandom file command since it also allows levels 3 and 4 to have blocks generated in sequence from file
void Controller::readFromFile(string filename, levels *l) {
    l->blocksFromFile(filename); 
}

void Controller::down(int n) { 
    for (int i = 0; i < n; ++i) {
        int val = this->getGrid()->down(this->turn);
        cout << *this->getGrid();
        if (val != 1) {
            this->changeTurn();
            break;
        } 
    }
}

void Controller::drop() {
    this->getGrid()->drop(this->turn);
    this->changeTurn();
}

void Controller::restart() {

}

void Controller::generate() { 
    // int n  = this->gr->getPlayer(s)->getLevel();
    // if (n == 0) { 
    //     levelzero *l = new levelzero();
    //}
    // else { 
    //     levels *level = this->gr->getPlayer(s)->getPtrLevel();
    //     this->gr->update(s, level->createBlock());
    // }
    // pass the player and a block 

    // Need to figure out a better way to accept string filename 
    string filename;
    if (this->turn == State::p1) { 
        filename = "sequence1.txt";
    } else {
        filename = "sequence2.txt";
    }
    try { 
        levels *l = this->getGrid()->getPlayer()->getPtrLevel();
        if(this->getGrid()->getPlayer()->getLevel() == 0){
            this->readFromFile(filename, l); // throws a string 
        }
        if (this->getGrid()->getPlayer()->getNextBlock() == nullptr) { 
            this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        } 
        Block *b = this->getGrid()->getPlayer()->getNextBlock();
        delete this->getGrid()->getPlayer()->getBlock();
        this->getGrid()->getPlayer()->setBlock(b);
        this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        this->getGrid()->update(this->turn);
    }
    catch (string &c) { cout << c << endl; }
    cout << *(this->getGrid()); 
}

