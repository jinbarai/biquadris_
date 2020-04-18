#include "controller.h"
using namespace std;

Controller::Controller(shared_ptr<Grid> g1, shared_ptr<Grid> g2, shared_ptr<TextDisplay> td, 
    int score, bool text, shared_ptr<Graphics> gr) {
    this->g1 = g1;
    this->g2 = g2;
    this->td = td;
    this->text = text;
    this->gr = gr;
    this->highscore = score;
    this->turn = State::p1;
}

shared_ptr<Grid> Controller::getGrid() {
    if  (this->turn == State::p1) {
        return this->g1;
    } else  { 
        return this->g2;
    }
}

void Controller::specialAction() {
    cout << "Congratultions on your Special Action!" << endl;
    cout << "Select one of the following: ";
    cout << "Blind, Heavy or Force" << endl;
    string s;
    cin >> s;
    const char c = s.at(0);
    if (c == 'B'|| c == 'b') {
        cout << "You have selected: Blind" << endl;
        this->blind();
    } else if  (c == 'H' || c == 'h') {
        cout << "You have selected: Heavy" << endl;
        this->heavy();
    } else if (c == 'F' || c == 'f') {
        char c;
        cin >> c;
        cout << "You have selected: Force " << c << endl;
        this->force(c);
    }  else { 
        cout << "Invalid choice. Special Action cancelled!" << endl;
    }
}

void Controller::blind() {
    if (this->turn == State::p1) {
        this->g2->getPlayer()->setBlind();
        if (!this->text) {
            this->gr->drawBlind(State::p2);
        }
    } else { 
        this->g1->getPlayer()->setBlind();
        if (!this->text) {
            this->gr->drawBlind(State::p1);
        }
    }
    cout << *this->getGrid(); // does not matter which Grid, just want to show blind 
}

void Controller::force(char c) {
    shared_ptr<Player> p;
    if (this->turn == State::p1) { 
        p = g2->getPlayer();
    } else {  
        p = g1->getPlayer();
    }
    Bool b = false;
    // to determine if it is heavy
    if (p->getLevel() >= 3) {
        b = true;
    }
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
}

void Controller::changeBlock(char c) {
    bool flag = false;
    bool heavyCommand = this->getGrid()->getPlayer()->getBlock()->isCommandHeavy();
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

void Controller::changeTurn() {
    if (!this->text && this->getGrid()->getPlayer()->getLevel() == 6) {
        this->getGrid()->fixBlind(this->turn);
    }
    if (this->getGrid()->getPlayer()->getScore() > this->highscore) {
        this->highscore = this->g1->getPlayer()->getScore();
        this->td->updateScore(this->highscore);
        if (!this->text) { 
            this->gr->changeScore(this->highscore);
        }
        cout << this->getGrid()->getPlayer()->getName() << " updated highscore!" << endl;
    } 
    if (this->turn == State::p1) {
        this->turn = State::p2;
        this->generate();
        return;
    } else { 
        this->turn = State::p1;
        this->generate();
        return;
    }
}

void Controller::levelup() {
    int level = this->getGrid()->getPlayer()->getLevel();
    // Cannot levelup if it already 6
    if (level == 6) {
        cout << "Max level reached!" << endl; 
        return;
    } 
    ++level;
    this->getGrid()->getPlayer()->changeLevel(level);
    if (!this->text) {
        this->getGrid()->getGraphics()->changeLevel();
    }
}

int Controller::getHighScore(){
    return this->highscore;
}

void Controller::leveldown() {
    int level = this->getGrid()->getPlayer()->getLevel();
    // Cannot level down if it already 0
    if (level == 0) {
        cout << "Min level reached!" << endl; 
        return;
    }
    --level;
    this->getGrid()->getPlayer()->changeLevel(level);
    if (!this->text) {
        this->gr->changeLevel();
    }
}
  
void Controller::startlevel(int n) { 
    this->g1->getPlayer()->changeLevel(n);
    this->g2->getPlayer()->changeLevel(n);
    if (!this->text) { 
        this->gr->changeLevel();
    }
}

void Controller::heavy(){
    if (this->turn == State::p1) {
        this->g2->getPlayer()->setSpecialHeavy(true);
    } else { 
        this->g1->getPlayer()->setSpecialHeavy(true);
    }
}

void Controller::move(int n, int dir) { 
    for (int i = 0; i < n; ++i) {
        int val = this->getGrid()->move(this->turn, dir);
        if (this->getGrid()->getPlayer()->getBlock()->isLevelHeavy()){
        // || this->getGrid()->getPlayer()->isLevelHeavy()){
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1){
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                this->changeTurn();
                return;
            }
        }
        if (this->getGrid()->getPlayer()->getBlock()->isCommandHeavy()){
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1) {
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                this->changeTurn();
                return;
            }
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1) {
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                this->changeTurn();
                return;
            }
        }
        if (this->getGrid()->getPlayer()->getLevel() != 6 && val) { 
            cout << *this->getGrid();
        }
    }
}

// Need this for norandom file command since it also allows levels 3 - 6 to have blocks generated in sequence from file
void Controller::readFromFile(string filename, shared_ptr<levels> l) {
    l->blocksFromFile(filename); 
}

void Controller::down(int n) { 
    for (int i = 0; i < n; ++i) {
        int val = this->getGrid()->down(this->turn);
        if (this->getGrid()->getPlayer()->getBlock()->isLevelHeavy()){
        //|| this->getGrid()->getPlayer()->isLevelHeavy()){
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1){
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                this->changeTurn();
                return;
            }
        }
        if (this->getGrid()->getPlayer()->getBlock()->isCommandHeavy()){
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1) {
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                this->changeTurn();
                return;
            } 
            val = this->getGrid()->down(this->turn);
            if (val == 0 || val == -1) {
                this->getGrid()->getPlayer()->setSpecialHeavy(false);
                this->changeTurn();
                return;
            }
        } 
        if (this->getGrid()->getPlayer()->getLevel() != 6) { 
            cout << *this->getGrid();
        }
        if (val != 1) {
            break;
        } 
    }
} 

string Controller::getKeyboardCommand() // used xev in console to get these numbers
{
    int key = this->getGrid()->getGraphics()->getXwindow()->getKeyCode();
    cout << "key: " << key << endl;
    // left = linux, right = mac
    if (key == 113 || key == 131) return "left"; //left arrow
    else if (key == 114 || key == 132) return "right";// right arrow
    else if (key == 116 || key == 133) return "down";// down arrow
    else if (key == 65 || key == 57) return "drop";// spacebar
    else if (key == 52 || key == 14) return "cw";// z
    else if (key == 53 || key == 15) return "ccw";// x
    else if (key == 29 || key == 24) return "restart";// y
    else if (key == 25 || key == 21) return "levelup";// w
    else if (key == 38 || key == 8) return "leveldown";// s
    else if (key == 9 || key == 61) return "end";//escape
    else return "";
}

void Controller::cw(int n) {
    //n = n % 4;
    for (int i = 0; i < n; ++i) {
       this->getGrid()->rotate(this->turn);
    }
    if (this->getGrid()->getPlayer()->getBlock()->isLevelHeavy()) this->down();
    if (this->getGrid()->getPlayer()->getLevel() != 6) { 
        cout << *this->getGrid();
    }
}

void Controller::ccw(int n) {
    //n = n % 4;
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

void Controller::clearVector(shared_ptr<levels> l) {
    l->clearVector();
}

shared_ptr<Grid> Controller::getG1() {
    return this->g1;
}

shared_ptr<Grid> Controller::getG2() {
    return this->g2;
}

void Controller::drop(int n) {
    bool flag = false; 
    for (int i = 0; i < n; ++i) {
        bool val = this->getGrid()->drop(this->turn);
        cout << *this->getGrid();
        if (val) {
          flag = true;
        }
        if (this->getGrid()->getPlayer()->isSpecialHeavy()){
            this->getGrid()->getPlayer()->setSpecialHeavy(false);
        }
        if (!this->text && this->getGrid()->getPlayer()->isBlind()) {
            this->getGrid()->getPlayer()->setBlind();
            this->getGrid()->fixBlind(this->turn);
        }
        if (i != n - 1) { 
            this->generate();
        }
    }
    if (flag) {
        this->specialAction();
    }
    this->changeTurn();
}

void Controller::random() {
    // If the pointer level is 3 - 6 only then the random function can be toggled on/off
    if (this->getGrid()->getPlayer()->getLevel() >= 3) {
        this->getGrid()->getPlayer()->getPtrLevel()->setRandom(false);
        this->getGrid()->getPlayer()->setFile("");
        shared_ptr <levels> l = this->getGrid()->getPlayer()->getPtrLevel();
        this->clearVector(l);
        this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        //cout << this->getGrid()->getPlayer()->getPtrLevel()->getRandom() << endl; 
    } else {
        string s = "Wrong level for toggling random/norandom option";
        cout << s << endl; 
    }
}

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
        //cout << t->getType() << endl;
        this->getGrid()->getPlayer()->setNextBlock(t);
    } else {
        string s = "Wrong level for toggling random/norandom option";
        cout << s << endl;
    }
}

void Controller::sequence(string filename) {

}

void Controller::restart() {
    string s1 = this->g1->getPlayer()->getName();
    string s2 = this->g2->getPlayer()->getName();
    shared_ptr<Player> p1 = make_shared<Player>(0, s1, 0, "sequence1.txt");
    shared_ptr<Player> p2 = make_shared<Player>(0, s2, 0, "sequence2.txt");
    this->g1->init(p1, this->text);
    this->g2->init(p2, this->text);
    if (!this->text) { 
        this->gr = make_shared<Graphics>(p1, p2, this->highscore);
    } else { 
        this->gr = nullptr;
    }
    this->td = make_shared<TextDisplay>(p1, p2, this->highscore);
    g1->setTD(this->td);
    g2->setTD(this->td);
    g1->setGraphics(this->gr);
    g2->setGraphics(this->gr);
    this->turn = State::p1;
    this->generate();
}

void Controller::generate() { 
    try { 
        shared_ptr<levels> l = this->getGrid()->getPlayer()->getPtrLevel();
        int level = this->getGrid()->getPlayer()->getLevel();
        if (!this->text && level == 6) {
            this->gr->level6(this->turn);
        }
        if(l->getRandom() == true) {
            this->readFromFile(this->getGrid()->getPlayer()->getFileName(), l); // throws a string 
        }
        if (this->getGrid()->getPlayer()->getNextBlock() == nullptr) { 
            this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        } 
        shared_ptr<Block> b = this->getGrid()->getPlayer()->getNextBlock();
        this->getGrid()->getPlayer()->setBlock(b);
        this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        if (!this->text) {
            this->gr->next();
        }
        this->getGrid()->update(this->turn);
    }
    catch (string &c) { cout << c << endl; }
    if (this->getGrid()->getPlayer()->getLevel() != 6) { 
        cout << *this->getGrid();
    }
}

Controller::~Controller() {}
