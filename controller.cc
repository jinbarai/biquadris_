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
  
  void Controller:: left() {

  }


  void Controller::startlevel(int n) { 
      this->gr->getPlayer("p1")->changeLevel(n);
      this->gr->getPlayer("p2")->changeLevel(n);
  }

//void right();
// void down();
