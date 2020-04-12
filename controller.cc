#include "controller.h"

Controller::Controller(Grid *g) {
    this->gr = g;
    this->turn = State::p1;
}

void Controller::changeTurn() {
    if (this->turn == State::p1) {
        this->turn = State::p2;
        return;
    } 
    this->turn = State::p1;
}

void Controller::levelup() {
    string s;
    if (this->turn == State::p1) {
        s = "p1";
    } else { 
        s = "p2";
    }
    int level = this->gr->getPlayer(s)->getLevel();
    ++level;
    this->gr->getPlayer(s)->changeLevel(level);
}

void Controller::leveldown() {
    string s;
    if (this->turn == State::p1) {
        s = "p1";
    } else { 
        s = "p2";
    }
    int level = this->gr->getPlayer(s)->getLevel();
    --level;
    this->gr->getPlayer(s)->changeLevel(level);
}
  
  void Controller::startlevel(int n) { 
      this->gr->getPlayer("p1")->changeLevel(n);
      this->gr->getPlayer("p2")->changeLevel(n);
  }

// called to move a block right 
void Controller::right() { 

}

// called to move a block left 
void Controller::left() { 

}

// Need this for norandom file command since it also allows levels 3 and 4 to have blocks generated in sequence from file
void Controller::readFromFile(string filename, levels *l) {
    l->blocksFromFile(filename); 
}

void Controller::restart() {

}

void Controller::generate() { 
    string s;
    if (this->turn == State::p1) {
        s = "p1";
    } else { 
        s = "p2";
    }
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
    if (s == "p1") { 
        filename = "sequence1.txt";
    } else if (s == "p2") {
        filename = "sequence2.txt";
    }
    try { 
        levels *l = this->gr->getPlayer(s)->getPtrLevel();
        this->readFromFile(filename, l); // throws a string 
        if (this->gr->getPlayer(s)->getNextBlock() == nullptr) { 
            this->gr->getPlayer(s)->setNextBlock(l->createBlock());
        } 
        Block *b = this->gr->getPlayer(s)->getNextBlock();
        delete this->gr->getPlayer(s)->getBlock();
        this->gr->getPlayer(s)->setBlock(b);
        this->gr->getPlayer(s)->setNextBlock(l->createBlock());
        this->gr->update(s, b);
    }
    catch (string &c) { cout << c << endl; }
    cout << *(this->gr); 
}

