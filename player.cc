#include "player.h"
using namespace std;

Player::Player(int x, string s, int lev, string fileName) {
    this->score = x;
    this->name = s;
    this->blind = false;
    this->b = nullptr;
    this->bnext = nullptr;
    this->file = fileName;
    if (lev < 0) { 
        lev = 0;
    } else if (lev > 6) { 
        lev = 0;
    }
    this->level = lev;
    if (lev == 0) {
        this->l =  make_shared<levelzero>(); // add notes based on level code
    } else if (lev == 1) {
        this->l  = make_shared<levelone>();
    } else if (lev == 2) {
        this->l  = make_shared<leveltwo>();
    } else if (lev == 3) {
        this->l  = make_shared<levelthree>();
    } else if (lev == 4) {
        this->l  = make_shared<levelfour>();
    }  else if (lev == 5) {
        this->l = make_shared<levelfive>();
    } else if (lev == 6) {
        this->l = make_shared<levelsix>();
    }
}

shared_ptr<Block> Player::getBlock() {
    return this->b;
}

shared_ptr<Block> Player::getNextBlock() {
    return this->bnext;
}

void Player::setBlock(shared_ptr<Block> b) { 
    this->b = b;
}

void Player::setNextBlock(shared_ptr<Block> b) { 
    this->bnext = b;

}

int Player::getScore() { 
    return this->score;
}

void Player::addScore(int x) { 
    this->score += x;
}

string Player::getName() {
    return this->name;
}

shared_ptr<levels> Player::getPtrLevel() {
    return this->l;
}

int Player::getLevel() { 
    return this->level;
}

void Player::setSpecialHeavy(bool n){
    this->specialCommandHeavy = n;
}

bool Player::isSpecialHeavy(){
    return this->specialCommandHeavy;
}

bool Player::isBlind() {
    return this->blind;
}

void Player::setBlind() {
    if (this->blind) {
        this->blind = false;
    } else { 
        this->blind = true;
    }
}/*
void Player::setLevelHeavy(bool b){
    this->levelHeavy = b;
}
bool Player::isLevelHeavy(){
    return  this->levelHeavy;
}
*/

void Player::changeLevel(int lev) {
    if (lev > 6) {
        return;
    } else if (lev < 0) {
        return;
    }
    this->level = lev;
    if (lev == 0) {
        this->l =  make_shared<levelzero>(); // add notes based on level code
     //   this->setLevelHeavy(false);
    } else if (lev == 1) {
        this->l  = make_shared<levelone>();
     ///   this->setLevelHeavy(false);
    } else if (lev == 2) {
        this->l  = make_shared<leveltwo>();
      //  this->setLevelHeavy(false);
    } else if (lev == 3) {
      //  this->setLevelHeavy(true);
        this->l  = make_shared<levelthree>();
    } else if (lev == 4) {
        this->l  = make_shared<levelfour>();
      //  this->setLevelHeavy(true);
    }  else if (lev == 5) {
        this->l = make_shared<levelfive>();
      //  this->setLevelHeavy(true);
    } else if (lev == 6) {
        this->l = make_shared<levelsix>();
      //  this->setLevelHeavy(true);
    }
}

string Player::getFileName(){
    return this->file;
}

void Player::setFile(string filename) {
    this->file = filename; 
}

Player::~Player() {}

