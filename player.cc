#include "player.h"
using namespace std;

Player::Player(int x, string s, levels *level, int lev) {
    this->score = x;
    this->name = s;
    this->l = level;
    this->level = lev;
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

void Player::changeLevel(levels *level, int lev) {
    delete this->l;
    this->l = level;
    this->level = lev;
}

