#include "controller.h"

Controller::Controller(Grid *g1, Grid *g2, TextDisplay *td, Graphics *gr) {
    this->g1 = g1;
    this->g2 = g2;
    this->td =  td;
    this->gr = gr;
    this->turn = State::p1;
}

Grid *Controller::getGrid() {
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
    if (c == 'B' || c == 'b') {
        cout << "You have selected: Blind" << endl;
        this->blind();
        cout << "Hello I made it back after doing blind!" << endl;
    } else if  (c == 'H' || c == 'h') {
        cout << "You have selected: Heavy" << endl;
        //this->heavy();
    } else if (c == 'F' || c == 'f') {
        char c;
        cin >> c;
        cout << "You have selected: Force" << c << endl;
        this->force(c);
    }
}

void Controller::blind() {
    if (this->turn == State::p1) {
        this->g2->getPlayer()->setBlind();
        this->gr->drawBlind(State::p2);
    } else { 
        this->g1->getPlayer()->setBlind();
        this->gr->drawBlind(State::p1);
    }
    cout << *this->getGrid(); // does not matter which Grid, just want to show blind 
}

void Controller::force(char c) {
    Player *p;
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
        delete p->getNextBlock();
        p->setNextBlock(new ZBlock(b));
    } else if (c == 'T' || c == 't') {
        delete p->getNextBlock();
        p->setNextBlock(new TBlock(b));
    } else if (c == 'O' || c == 'o') {
        delete p->getNextBlock();
        p->setNextBlock(new OBlock(b));
    } else if (c == 'S' || c == 's') {
        delete p->getNextBlock();
        p->setNextBlock(new SBlock(b));
    } else if (c == 'I' || c == 'i') {
        delete p->getNextBlock();
        p->setNextBlock(new IBlock(b));
    } else if (c == 'J' || c == 'j') {
        delete p->getNextBlock();
        p->setNextBlock(new JBlock(b));
    } else if (c == 'L' || c == 'L') {
        delete p->getNextBlock();
        p->setNextBlock(new LBlock(b));
    } else { 
        cout << "Invalid Character, Force cancelled" << endl;
    }
}

void Controller::changeBlock(char c) {
    bool b = false;
    if (this->getGrid()->getPlayer()->getLevel() >= 3) {
        b = true;
    }
    Block *b;
    if (c == 'Z' || c == 'z') { 
        this->theGrid()->changeBlock(new ZBlock(b));
    } else if (c == 'T' || c == 't') {
        this->theGrid()->changeBlock(new TBlock(b));
    } else if (c == 'O' || c == 'o') {
        this->theGrid()->changeBlock(new OBlock(b));
    } else if (c == 'S' || c == 's') {
        this->theGrid()->changeBlock(new SBlock(b));
    } else if (c == 'I' || c == 'i') {
        this->theGrid()->changeBlock(new IBlock(b));
    } else if (c == 'J' || c == 'j') {
        this->theGrid()->changeBlock(new JBlock(b));
    } else if (c == 'L' || c == 'l') {
        this->theGrid()->changeBlock(new LBlock(b));
    } else { 
        cout << "Invalid Character: " << c << "command cancelled" << endl;
    }
}

void Controller::changeTurn() {
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
    ++level;
    this->getGrid()->getPlayer()->changeLevel(level);
    if (this->getGrid()->getGraphics()) {
        this->getGrid()->getGraphics()->changeLevel();
    }
}

void Controller::leveldown() {
    int level = this->getGrid()->getPlayer()->getLevel();
    if (level == 0) return;
    --level;
    this->getGrid()->getPlayer()->changeLevel(level);
    if (this->getGrid()->getGraphics()) {
        this->getGrid()->getGraphics()->changeLevel();
    }
}
  
void Controller::startlevel(int n) { 
    this->g1->getPlayer()->changeLevel(n);
    this->g2->getPlayer()->changeLevel(n);
    this->g1->getGraphics()->changeLevel();
    this->g2->getGraphics()->changeLevel();
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
        this->getGrid()->move(this->turn, dir);
    }
}

// Need this for norandom file command since it also allows levels 3 - 6 to have blocks generated in sequence from file
void Controller::readFromFile(string filename, levels *l) {
    l->blocksFromFile(filename); 
}

void Controller::down(int n) { 
    for (int i = 0; i < n; ++i) {
        int val = this->getGrid()->down(this->turn);
        cout << *this->getGrid();
        if (val != 1) {
            break;
        } 
    }
}

void Controller::cw(int n) {
    for (int i = 0; i < n; ++i) {
        this->getGrid()->rotate(this->turn);
    }
    if (this->getGrid()->getPlayer()->getBlock()->isHeavy()) this->down();
    cout << *this->getGrid();
}

void Controller::ccw(int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < 3; i++) {
            this->getGrid()->rotate(this->turn);
        }
    }
    if (this->getGrid()->getPlayer()->getBlock()->isHeavy()) this->down();
    cout << *this->getGrid();
}

void Controller::drop(int n) {
    bool flag = false; 
    for (int i = 0; i < n; ++i) {
        bool val = this->getGrid()->drop(this->turn);
        if (val) {
          flag = true;
         }
        if (this->getGrid()->getPlayer()->isSpecialHeavy()){
            this->getGrid()->getPlayer()->setSpecialHeavy(false);
        }
        if (this->getGrid()->getPlayer()->isBlind()) {
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

void Controller::restart() {
    string s1 = this->g1->getPlayer()->getName();
    string s2 = this->g2->getPlayer()->getName();
    delete this->td;
    delete this->gr;
    delete this->g1;
    delete this->g2;
    Player *p1 = new Player(0, s1, 0);
    Player *p2 = new Player(0, s2, 0);
    this->g1 = new Grid();
    this->g2 = new Grid();
    this->g1->init(p1);
    this->g2->init(p2);
    this->td = new TextDisplay(p1, p2);
    this->gr = new Graphics{p1, p2};
    g1->setTD(this->td);
    g2->setTD(this->td);
    g1->setGraphics(this->gr);
    g2->setGraphics(this->gr);
    this->turn = State::p1;
    this->generate();
}

void Controller::random() {
    // If the pointer level is 3 - 6 only then the random function can be toggled on/off
    if (this->getGrid()->getPlayer()->getLevel() >= 3) {
        this->getGrid()->getPlayer()->getPtrLevel()->setRandom(false);
    } else {
        string s = "Wrong level for toggling random/norandom option";
        cout << s << endl; 
    }
}

void Controller::norandom(){ 
    // If the pointer level is 3 - 6 only then the random function can be toggled on/off
    if (this->getGrid()->getPlayer()->getLevel() >= 3) {
        this->getGrid()->getPlayer()->getPtrLevel()->setRandom(true); 

    } else {
        string s = "Wrong level for toggling random/norandom option";
        cout << s << endl;
    }
}

void Controller::sequence(string filename) {

}

void Controller::generate() { 
    try { 
        levels *l = this->getGrid()->getPlayer()->getPtrLevel();
        if(l->getRandom() == true) {
            this->readFromFile(this->getGrid()->getPlayer()->getFileName(), l); // throws a string 
        }
        if (this->getGrid()->getPlayer()->getNextBlock() == nullptr) { 
            this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        } 
        Block *b = this->getGrid()->getPlayer()->getNextBlock();
        delete this->getGrid()->getPlayer()->getBlock();
        this->getGrid()->getPlayer()->setBlock(b);
        this->getGrid()->getPlayer()->setNextBlock(l->createBlock());
        this->gr->next();
        this->getGrid()->update(this->turn);
    }
    catch (string &c) { cout << c << endl; }
    cout << *(this->getGrid()); 
}

Controller::~Controller() {
    delete this->g1;
    delete this->g2;
    delete this->td;
}