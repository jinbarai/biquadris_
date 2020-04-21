#include "player.h"
using namespace std;

/* Player::Player(int x, string s, int lev, string fileName)
 * a player is able to be constructed with string s
 * as ther name, level 0 for the level they are starting with and 
 * a string fileName if they are given a command line argument with 
 * their filename, 
 */
Player::Player(string s, int lev, bool bonus, string fileName) : name{s} {
    this->score = 0;
    this->blind = false;
    this->bonus = bonus;
    // their next block defaults to null upon construction 
    this->b = nullptr;
    // next block set to null 
    this->bnext = nullptr;
    this->file = fileName;
    if (this->bonus) {
        if (lev < 0 || lev > 6) { // if an incorrect level is provided
            // it defaults to zeor
            lev = 0;
        } 
        
    } else { 
        if (lev < 0 || lev > 4) { 
            lev = 0;
        }
    }
    this->level = lev;
        // attaches the correct level pointer to the player 
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

/* Player::getBlock() 
 * This method returns the players next block 
 * Used with Controller::generate, and in Grid 
 * to move/rotate the block. 
 */
shared_ptr<Block> Player::getBlock() {
    return this->b;
}

/* Player::getNextBlock()
 * This is similar to Player::getBlock() but returns the 
 * players NEXT block (the one to be played their next turn)
 */
shared_ptr<Block> Player::getNextBlock() {
    return this->bnext;
}

/* Player::setBlock(Block *b)
 * This is used to set the players next block
 * This is used with Grid::changeBlock and Controller::generate
 */
void Player::setBlock(shared_ptr<Block> b) { 
    this->b = b;
}

/* Player::setNextBlock(Block *b)
 * Similar to Player::setBlock but used for the players NEXT 
 * block, for thir next turn. 
 */
void Player::setNextBlock(shared_ptr<Block> b) { 
    this->bnext = b;

}

/* Player::getScore()
 * This returns the players current score 
 */
int Player::getScore() { 
    return this->score;
}

/* Player::addScore(int x) 
 * this is used to update the players score
 * with Grid::rowClear()
 */
void Player::addScore(int x) { 
    this->score += x;
}

/* Player::Player(int x, string s, int lev, string fileName)
 * This returns the users inputed name. This is essentially constant
 * and never changed during the programs runtime. 
 */
string Player::getName() {
    return this->name;
}


/* Player::getPtrLevel() 
 * this is used to returns the players level pointer
 * to create a block in Controller::generate. 
 */
shared_ptr<levels> Player::getPtrLevel() {
    return this->l;
}
/* Player::getLevel()
 * This returns the players current level (as an int)
 */
int Player::getLevel() { 
    return this->level;
}

/* Player::setSpecialHeavy(bool n)
 * This sets the current players heavy status for 
 * the specialAction heavy command. 
 */
void Player::setSpecialHeavy(bool n){
    this->specialCommandHeavy = n;
}

/* Player::isSpecialHeavy()
 * This is used to determine if a player is experiencing 
 * the specialAction heavy. 
 */
bool Player::isSpecialHeavy(){
    return this->specialCommandHeavy;
}

/* Player::isBlind()
 * This is used to determine if a player is experiencing the
 * specialAction heavy. Used by textdisplay.cc 
 */
bool Player::isBlind() {
    return this->blind;
}

/* Player::setBlind()
 * This is used to set a player to a blind setting if their
 * opponent select the Blind special command option. Works 
 * with toggling behaviour. 
 */
void Player::setBlind() {
    if (this->blind) {
        this->blind = false;
    } else { 
        this->blind = true;
    }
}

void Player::changeBonus(bool b) {
    this->bonus = b;
}

/* Player::changeLevel(int lev)
 * Used to change the players level and called by the
 * Controller::levelup and Controller::leveldown. 
 * Has no effect if called with an incorrect level. 
 */
void Player::changeLevel(int lev) {
    if (this->bonus && lev > 6) {
        return;
    } else if (!this->bonus && lev > 4) { 
        return;
    } else if (lev < 0) {
        return;
    }
    this->level = lev;
        // attaches the correct level pointer to the player 
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

/* Player::getFileName()
 * This is used to determine the current players file. 
 */
string Player::getFileName(){
    return this->file;
}

/* Player::setFile(string Filename)
 * This is used to set the current players fille. 
 */
void Player::setFile(string filename) {
    this->file = filename; 
}

