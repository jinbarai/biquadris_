#include "controller.h"
using namespace std;

/* 
 * Controller::Controller
 * This constructor is used to construct the Controller. takes in the grid's, TextDisplay, 
 * Graphics, the program's highest score whether or not the program is being run in text mode
 */
Controller::Controller(shared_ptr<Grid> g1, shared_ptr<Grid> g2, shared_ptr<TextDisplay> td, 
    int score, bool text, shared_ptr<Graphics> gr, bool bonus) {
    this->g1 = g1;
    this->g2 = g2;
    this->td = td;
    this->text = text; 
    // to determine if program is running in text mode 
    this->gr = gr;
    this->highscore = score;
    this->bonus = bonus;
    // used to determine the highest score yet 
    this->turn = State::p1; 
    /* 
     * defaults turn to Player 1
     * Note: this default behaviour is NOT modifiable 
     */
}

/* 
 * Controller::getGrid()
 * This is used to obtain the correct Grid of the current turn's player
 * This was implimented in order to prevent having to check which grid 
 * must be called each time for cleaner code 
 */ 
shared_ptr<Grid> Controller::getGrid() {
    if  (this->turn == State::p1) {
        return this->g1;
    } else  { 
        return this->g2;
    }
}

/* 
 * Controller::setKeyboard(bool k)
 * This is used if the Bonus feature "-keyboardmode" is  used
 * it will set the bool to be true and hence the program will have 
 * a different behaviour when wanting to execute commands 
 * Note: refer to the main.cc for more information 
 */ 
void Controller::setKeyboard(bool k) {
    this->keyboard = k;

}

/* 
 * Controller::specialAction()
 * This is used to allow the user to select which special Action they 
 * want to select. This is called from drop, if the player accurately 
 * cleared 2 or more rows at once! 
 * Effects: uses I/O seperate from main.cc 
 */ 

void Controller::specialAction(char c, char b = ' ') {
    if (c == 'B' || c == 'b') {
        cout << "You have selected: Blind" << endl;
        this->blind();
    } else if (c == 'H' || c == 'h') {
        cout << "You have selected: Heavy" << endl;
        this->heavy();
    } else if (c == 'F' || c == 'f') {
        cout << "You have selected: Force " << b << endl;
        this->force(b);
    }  else { 
        cout << "Invalid choice. Special Action cancelled!" << endl;
        this->changeTurn();
    }
}

void Controller::setSpecialAction(bool b) {
    this->ActionMode = b;
}

/* 
 * Controller::blind()
 * This is used in order to accurately cause the special Affect 
 * blind. This is called from Controller::specialAction(). 
 */ 
void Controller::blind() {
    if (this->turn == State::p1) {
        this->g2->getPlayer()->setBlind();
        if (!this->text) { // if the program is in text mode 
        // graphics do not need to be updated 
            this->gr->drawBlind(State::p2);
        }
    } else { 
        this->g1->getPlayer()->setBlind();
        if (!this->text) {
            this->gr->drawBlind(State::p1);
        }
    }
    // does not matter which grid is called because
    // the overloaded << operator prints both grids at once!
    // that is why getGrid() is used instead of the 
    // particular players turn
    this->changeTurn();
    cout << *this->getGrid(); // does not matter which Grid, just want to show blind 
}

/* 
 * Controller::force(char c)
 * This is used in order to accurately cause the special Affect 
 * force. This is called from Controller::specialAction(). 
 * Note: this changes the oponent players next Block! 
 * Effects: May cause output if invalid character (c) is supplied 
 */ 
void Controller::force(char c) {
    shared_ptr<Player> p;
    // we want to determine the oponent's turn 
    // and hence want to look for which player in particular
    // we are looking for 
    if (this->turn == State::p1) { 
        p = g2->getPlayer();
    } else {  
        p = g1->getPlayer();
    }
    bool b = false; 
    // to determine if it is heavy (levels >= 3)
    if (p->getLevel() >= 3) {
        b = true;
    }
    // determines which block to create: 
    if (c == 'Z' || c == 'z') { 
        p->setNextBlock(make_shared<ZBlock>(b));
    } else if (c == 'T' || c == 't') {
        p->setNextBlock(make_shared<TBlock>(b));
    } else if (c == 'O' || c == 'o') {
        p->setNextBlock(make_shared<OBlock>(b));
    } else if (c == 'S' || c == 's') {
        p->setNextBlock(make_shared<SBlock>(b));
    } else if (c == 'I' || c == 'i') {
        p->setNextBlock(make_shared<IBlock>(b));
    } else if (c == 'J' || c == 'j') {
        p->setNextBlock(make_shared<JBlock>(b));
    } else if (c == 'L' || c == 'L') {
        p->setNextBlock(make_shared<LBlock>(b));
    } else { 
        cout << "Invalid Character, Force cancelled" << endl;
    }
    this->changeTurn();
}
/* 
 * Controller::changeBlock(char c)
 * This is called from main.cc of an I/J/S/L/O/T/Z command is provided 
 * Effects: may cause output if invalid c is supplied  
 */ 
void Controller::changeBlock(char c) {
    bool flag = false; // used to determine if the behaviour 
    // is heavy (levels >= 3)
    bool heavyCommand = this->getGrid()->getPlayer()->getBlock()->isCommandHeavy();
    // used to determine if the current block is under specialAction Heavy 
    // to prevent the player from changing block to avoid this affect 
    if (this->getGrid()->getPlayer()->getLevel() >= 3) {
        flag = true;
    } 
    if (c == 'Z' || c == 'z') { 
        this->getGrid()->changeBlock(this->turn, make_shared<ZBlock>(flag));
    } else if (c == 'T' || c == 't') {
        this->getGrid()->changeBlock(this->turn, make_shared<TBlock>(flag));
    } else if (c == 'O' || c == 'o') {
        this->getGrid()->changeBlock(this->turn, make_shared<OBlock>(flag));
    } else if (c == 'S' || c == 's') {
        this->getGrid()->changeBlock(this->turn, make_shared<SBlock>(flag));
    } else if (c == 'I' || c == 'i') {
        this->getGrid()->changeBlock(this->turn, make_shared<IBlock>(flag));
    } else if (c == 'J' || c == 'j') {
        this->getGrid()->changeBlock(this->turn, make_shared<JBlock>(flag));
    } else if (c == 'L' || c == 'l') {
        this->getGrid()->changeBlock(this->turn, make_shared<LBlock>(flag));
    } else { 
        cout << "Invalid Character: " << c << endl;
        return;
    }
    this->getGrid()->getPlayer()->getBlock()->makeCommandHeavy(heavyCommand);
}

/* 
 * Controller::changeTurn()
 * This function is called in drop and will change the current player's turn. 
 * If the player is set to specialAction Blind, it will revert back
 * If the player is in level 6 with graphics mode (hence this->text = false), 
 * it will fix the graphics and revert to normal. 
 * If a player exceeded highscore in their move, it will be checked here. 
 * Effects: will produce output if the player exceeded high score 
 */ 
void Controller::changeTurn() {
    // if the player was set to Blind due to a special Action 
    if (this->getGrid()->getPlayer()->isBlind()) {
        this->getGrid()->getPlayer()->setBlind();
        if (!this->text) { // will call fixBlind on graphics
        // if is not text mode 
            this->getGrid()->fixBlind(this->turn);
        }
    }
    // if it is level 6 and the player was experiencing the affect of 
    // ther grid being hidden and text mode was not selected, it will 
    // show the player their grid now 
    if (!this->text && this->getGrid()->getPlayer()->getLevel() == 6) {
        this->getGrid()->fixBlind(this->turn);
    }
    // if the player updated highscore. 
    if (this->getGrid()->getPlayer()->getScore() > this->highscore) {
        this->highscore = this->g1->getPlayer()->getScore();
        this->td->updateScore(this->highscore);
        if (!this->text) { 
            this->gr->changeScore(this->highscore);
        }
        cout << this->getGrid()->getPlayer()->getName() << " updated highscore!" << endl;
    } 
    // changes to other players turn 
    if (this->turn == State::p1) {
        this->turn = State::p2;
        this->generate();
    } else { 
        this->turn = State::p1;
        this->generate();
    }
}

/* 
 * Controller::levelup()
 * Called from main.cc, used to increase the current players level
 * Note: this can only be called by the intended player (the opponent
 * can not increase your level).
 * Effects: if levelup is passed when level == 6, it will return output 
 */ 
void Controller::levelup() {
    int level = this->getGrid()->getPlayer()->getLevel();
    // Cannot levelup if it already 6
    if (this->bonus && level == 6) {
        cout << "Max level reached!" << endl; 
        return;
    } else if (!this->bonus && level == 4) { 
        cout << "Max level reached!" << endl; 
        return;
    } 
    ++level;
    this->getGrid()->getPlayer()->changeLevel(level);
    if (!this->text) { // will not change graphics 
    // if text mode is proviided 
        this->gr->changeLevel();
    }
    cout << *this->getGrid();
}

/* 
 * Controller::getHighScore()
 *  will return the Controller's highscore  
 */ 
int Controller::getHighScore(){
    return this->highscore;
}

/* 
 * Controller::leveldown()
 * Used to level down by the player, called by main.cc. 
 * This has the same rules as levelup(). 
 * Effects: will produce output if level == 0.
 */ 
void Controller::leveldown() {
    int level = this->getGrid()->getPlayer()->getLevel();
    // Cannot level down if it already 0
    if (level == 0) {
        cout << "Min level reached!" << endl; 
        return;
    }
    --level;
    this->getGrid()->getPlayer()->changeLevel(level);
    if (!this->text) { // will not change graphcis
    // if textmode is set 
        this->gr->changeLevel();
    }
    cout << *this->getGrid();
}

/* 
 * Controller::startlevel(int n)
 * will change the levels of both players
 * Note: this can ONLY be called at the start of the game
 * where its intended use is the "-startlevel" flag
 */   
void Controller::startlevel(int n) { 
    this->g1->getPlayer()->changeLevel(n);
    this->g2->getPlayer()->changeLevel(n);
    if (!this->text) { // if not text mode, will
    // update the graphics 
        this->gr->changeLevel();
    }
}

/* 
 * Controller::heavy()
 * This is used in order to accurately cause the special Affect 
 * heavy. This is called from Controller::specialAction(). 
 * Will set the players specialHeavy parameter 
 */ 
void Controller::heavy(){
    if (this->turn == State::p1) {
        this->g2->getPlayer()->setSpecialHeavy(true);
    } else { 
        this->g1->getPlayer()->setSpecialHeavy(true);
    }
    this->changeTurn();
}

/* 
 * Controller::move(int n, int dir)
 * This is used to move left and right for the player. 
 * n acts as the multipliar for the command 
 * Note: the graphics will be updated by grid.cc if changes occur, not 
 * through the Controller (Observer Design Pattern).
 * Effects: will output the grid 
 */ 
void Controller::move(int n, int dir) { 
    // used for loop for multiplier n 
    for (int i = 0; i < n; ++i) {
        int val = this->getGrid()->move(this->turn, dir);
        if (this->getGrid()->getPlayer()->getBlock()->isLevelHeavy()){
        // || this->getGrid()->getPlayer()->isLevelHeavy()){
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1){
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                drop();
                return;
            }
        } // used to determine the heavy nature of the blocks. 
        if (this->getGrid()->getPlayer()->getBlock()->isCommandHeavy()){
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1) {
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                drop();
                return;
            }
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1) {
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                drop();
                return;
            }
        } // if the game is NOT in Level 6 mode (grid hidden) and if 
        // there was an actual change by the command, then the grid 
        // should output the graphics. 
        if (this->getGrid()->getPlayer()->getLevel() != 6 && val) { 
            cout << *this->getGrid();
        }
    }
}

/* 
 * Controller::readFromFile
 * Need this for norandom file command since it also allows levels 3 - 6 to
 * have blocks generated in sequence from file
 */
void Controller::readFromFile(string filename, shared_ptr<levels> l) {
    l->blocksFromFile(filename); 
}

/* 
 * Controller::down(int n)
 * n is the multipliar passed to the down command 
 * This would be called from main.cc
 * Effects: if a down move happens, will output grid
 */ 
void Controller::down(int n) { 
    // for loop for multipliar 
    for (int i = 0; i < n; ++i) {
        int val = this->getGrid()->down(this->turn);
        if (this->getGrid()->getPlayer()->getBlock()->isLevelHeavy()){
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1){
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                drop();
                // if it is not possible to move down anymore, shuld stop. 
                return;
            }
        }
        // used to determine special action heavy 
        if (this->getGrid()->getPlayer()->getBlock()->isCommandHeavy()){
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1) {
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                drop();
                return;
            } 
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1) {
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                drop();
                return;
            }
        } 
        // grid will only be outputted if it is not in level 6 hide mode  
        if (this->getGrid()->getPlayer()->getLevel() != 6) { 
            cout << *this->getGrid();
        }
        if (val != 1) {
            break;
        } 
    }
} 
/* saving key commands 
 * mac: 
 * 1: 26
 * 2: 27
 * 3: 28
 * linux: 
 * 1: 10
 * 2: 11
 * 3: 12
 */ 

/* 
 * Controller::getKeyboardCommand()
 * BONUS FEATURE 
 * This is used in order to use the particular key commands provided if 
 * "-keyboardmode" is provided. 
 * Note: cannot be used if program is in "-text" mode. 
 */ 
string Controller::getKeyboardCommand() // used xev in console to get these numbers
{
    // key is updated by graphics 
    int key = this->gr->getXwindow()->getKeyCode();
    // left = linux, right = mac
    if (key == 113 || key == 131) return "left"; //left arrow
    else if (key == 114 || key == 132) return "right";// right arrow
    else if (key == 116 || key == 133) return "down";// down arrow
    else if (key == 65 || key == 57) return "drop";// spacebar
    else if (key == 111 || key == 134) return "clockwise";// up
    else if (key == 52 || key == 14) return "counterclockwise";// z
    else if (key == 29 || key == 24) return "restart";// y
    else if (key == 25 || key == 21) return "levelup";// w
    else if (key == 38 || key == 8) return "leveldown";// s
    else if (key == 9 || key == 61) return "end";//escape
    /* in case more commands want to be added 
    else if (key == 10 || key == 26) return "blind";
    else if (key == 11 || key == 27) return "heavy";
    else if (key == 12 || key == 28) return "force";
    */
    else return ""; // return empty string if not possible 
}

/* 
 * Controller::cw(int n)
 * n is the multipliar passed from main.cc 
 * will rotate the grid n % 4 times (for efficiency).
 */ 
void Controller::cw(int n) {
    n = n % 4;
    for (int i = 0; i < n; ++i) {
       this->getGrid()->rotate(this->turn);
    }
    if (this->getGrid()->getPlayer()->getBlock()->isLevelHeavy()) this->down();
    // ensures program does not print whe in hiding mode for level 6
    if (this->getGrid()->getPlayer()->getLevel() != 6) { 
        cout << *this->getGrid();
    }
}

/* 
 * Controller::ccw()
 * This is identical to cw, however moves in the opposite direction!
 */ 
void Controller::ccw(int n) {
    n = n % 4;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < 3; i++) {
            this->getGrid()->rotate(this->turn);
        }
    }
    if (this->getGrid()->getPlayer()->getBlock()->isLevelHeavy()) this->down();
    if (this->getGrid()->getPlayer()->getLevel() != 6) { 
        cout << *this->getGrid();
    }
}

/* 
 * Controller::clearVector()
 * Used to clear the vector of blocks from the players 
 * provided fle 
 * Note: see player.cc & levels.cc for more information. 
 */ 
void Controller::clearVector(shared_ptr<levels> l) {
    l->clearVector();
}

/* 
 * Controller::getG1()
 * Will specifically return Player 1's grid 
 */ 
shared_ptr<Grid> Controller::getG1() {
    return this->g1;
}

/* 
 * Controller::getG2()
 * Will return Player 2's grid
 */
shared_ptr<Grid> Controller::getG2() {
    return this->g2;
}

/* 
 * Controller::drop(int n)
 * n acts the multipliar 
 * Drop works with grid.cc drop in order to accurately drop a block
 * 
 */ 
void Controller::drop(int n) {
    bool flag = false; 
    // flag is used to determine if 2 or more rows were cleared, and if so 
    // will trigger a special Action. 
    for (int i = 0; i < n; ++i) {
        bool val = this->getGrid()->drop(this->turn); 
        // val will determine if specialAction should be called or not 
        // does not check for level6 because even level 6 is visible after a drop
        cout << *this->getGrid();
        if (val) {
          flag = true;
        }
        if (this->getGrid()->getPlayer()->isSpecialHeavy()){
            this->getGrid()->getPlayer()->setSpecialHeavy(false);
        }
        if (i != n - 1) { 
            this->generate();
        }
    }
    if (flag) {
        this->ActionMode= true;
        throw SpecialAction();
    }  
    else { 
        this->changeTurn(); 
    // calls changeTurn because the players turn is done!
    }
}

bool Controller::isSpecialAction() {
    return this->ActionMode;
}

/* 
 * Controller::random()
 * If the random commamd from main.cc is called, it will revert the 
 * user to use randomized block values. 
 * Note: main.cc may accept a multiplier, but it is not used 
 * by the function. This command has no affects on levels 0-2. 
 */ 
void Controller::random() {
    // If the pointer level is 3 - 6 only then the random function can be toggled on/off
    if (this->getGrid()->getPlayer()->getLevel() >= 3) {
        this->getGrid()->getPlayer()->getPtrLevel()->setRandom(false);
        this->getGrid()->getPlayer()->setFile("");
        shared_ptr <levels> l = this->getGrid()->getPlayer()->getPtrLevel();
        this->clearVector(l);
        this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
    } else {
        string s = "Wrong level for toggling random/norandom option";
        cout << s << endl; 
    }
}

/* 
 * Controller::norandom(string filename)
 * If the norandom commamd from main.cc is called, it will change 
 * the user to have blocks called from the string filename! 
 * Note: main.cc may accept a multiplier, but it is not used 
 * by the function. This command has no affects on levels 0-2. 
 */ 
void Controller::norandom(string filename){ 
    // If the pointer level is 3 - 6 only then the random function can be toggled on/off
    if (this->getGrid()->getPlayer()->getLevel() >= 3) {
        this->getGrid()->getPlayer()->getPtrLevel()->setRandom(true); 
        this->getGrid()->getPlayer()->setFile(filename); 
        shared_ptr<levels> l = this->getGrid()->getPlayer()->getPtrLevel();
        string fl = this->getGrid()->getPlayer()->getFileName();
        this->clearVector(l);
        this->readFromFile(fl, l);
        // gives block type of old file 
        shared_ptr<Block> t = l->createBlock();
        this->getGrid()->getPlayer()->setNextBlock(t);
    } else {
        string s = "Wrong level for toggling random/norandom option";
        cout << s << endl;
    }
}

/* 
 * Controller::restart()
 * This is used to restart the whole game (does not change
 * highscore, or "-text" or "-keyboard" flags
 * Will revert the turn back to Player 1. 
 * Note: will save old player name's (for easier quick testing).
 */ 
void Controller::restart() {
    // Will store prvious names from when game was first started, and will 
    // revert players back to default sequence files. 
    string s1 = this->g1->getPlayer()->getName();
    string s2 = this->g2->getPlayer()->getName();
    shared_ptr<Player> p1 = make_shared<Player>(s1, 0, this->bonus, "sequence1.txt");
    shared_ptr<Player> p2 = make_shared<Player>(s2, 0, this->bonus, "sequence2.txt");
    // does not create new grids, simply re-initalizes them 
    this->g1->init(p1, this->text);
    this->g2->init(p2, this->text);
    // will reinitalize the graphics! 
    if (!this->text) { 
        this->gr->init(p1, p2, this->highscore);
    }
    // creates a new TextDisplay! 
    this->td = make_shared<TextDisplay>(p1, p2, this->highscore);
    // sets the TextDisplay for the user. 
    g1->setTD(this->td);
    g2->setTD(this->td);
    g1->setGraphics(this->gr);
    g2->setGraphics(this->gr);
    // defaults turn to Player 1! 
    this->turn = State::p1;
    // will call generate to start the turn automaticall 
    this->generate();
}

bool Controller::getBonus() {
    return this->bonus;
}

void Controller::changeBonus(bool b) {
    this->bonus = b;
}

/* 
 * Controller::generate()
 * Used to generate the block for the current player. If the player's next 
 * block is not null, it will save that as the current block. Otherwise, 
 * it will set both blocks! 
 */ 
void Controller::generate() { 
    try { 
        shared_ptr<levels> l = this->getGrid()->getPlayer()->getPtrLevel();
        // saves the level ptr to create the player's next Block 
        // from the level ptr 
        int level = this->getGrid()->getPlayer()->getLevel();
        if (!this->text && level == 6) {
            this->gr->level6(this->turn);
        } // checks if random is set for the Player
        if(l->getRandom() == true) {
            this->readFromFile(this->getGrid()->getPlayer()->getFileName(), l); // throws a string 
        }
        if (this->getGrid()->getPlayer()->getNextBlock() == nullptr) { 
            this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        } 
        // creates a block to be passed to the Grid.cc 
        shared_ptr<Block> b = this->getGrid()->getPlayer()->getNextBlock();
        this->getGrid()->getPlayer()->setBlock(b);
        this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        if (!this->text) { // will update the Graphics if not "-text" mode. 
            this->gr->next();
        }
        // will update the grid with the current player's state (hence 
        // which player's turn it is).
        this->getGrid()->update(this->turn);
    }
    catch (string &c) { cout << c << endl; }
    // will only output if not being hidden by level 6 hide mode 
    if (this->getGrid()->getPlayer()->getLevel() != 6) { 
        cout << *this->getGrid();
    }
}
