#include "player.h"
using namespace std;

Player::Player(int x, string s, int lev) {
    this->score = x;
    this->name = s;
    this->blind = false;
    if (lev < 0) { 
        lev = 0;
    } else if (lev > 4) { 
        lev = 0;
    }
    this->level = lev;
    if (lev == 0) {
        this->l =  new levelzero(); // add notes based on level code
    } else if (lev == 1) {
        this->l  = new levelone();
    } else if (lev == 2) {
         this->l  = new leveltwo();
    } else if (lev == 3) {
        this->l  = new levelthree();
    } else if (lev == 4) {
        this->l  = new levelfour();
    }  else if (lev == 5) {
        this->l =  new levelfive();
    } else if (lev == 6) {
        this->l = new levelsix();
    }
}

Block *Player::getBlock() {
    return this->b;
}

Block *Player::getNextBlock() {
    return this->bnext;
}

void Player::setBlock(Block *b) { 
    this->b = b;
}

void Player::setNextBlock(Block *b) { 
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

levels *Player::getPtrLevel() {
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
}

void Player::changeLevel(int lev) {
    if (lev > 6) {
        return;
    } else if (lev < 0) {
        return;
    }
    delete this->l;
    this->level = lev;
    if (lev == 0) {
        this->l =  new levelzero(); // add notes based on level code
    } else if (lev == 1) {
        this->l  = new levelone();
    } else if (lev == 2) {
         this->l  = new leveltwo();
    } else if (lev == 3) {
        this->l  = new levelthree();
    } else if (lev == 4) {
        this->l  = new levelfour();
    } else if (lev == 5) {
        this->l =  new levelfive();
    } else if (lev == 6) {
        this->l = new levelsix();
    }
}

Player::~Player() { 
    delete this->b;
    delete this->bnext;
    delete this->l;
}

