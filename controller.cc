#include "controller.h"

Controller::Controller(Grid *g1, Grid *g2, TextDisplay *td) {
    this->g1 = g1;
    this->g2 = g2;
    this->td =  td;
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
    cout << "entered here" << endl;
    if (this->turn == State::p1) {
        this->g2->getPlayer()->setSpecialHeavy(true);
        cout << "entered 52" << endl;
    } else { 
        this->g1->getPlayer()->setSpecialHeavy(true);
        cout << "entered 55" << endl;
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
    cout << *this->getGrid();
}

void Controller::ccw(int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < 3; i++) {
            this->getGrid()->rotate(this->turn);
        }
        cout << *this->getGrid();
    }
}

void Controller::drop() {
    int val = this->getGrid()->drop(this->turn);
    if (this->getGrid()->getPlayer()->isSpecialHeavy()){
        this->getGrid()->getPlayer()->setSpecialHeavy(false);
    }
    //if (val);
    this->changeTurn();
}

void Controller::restart() {

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
    // pass in a filename to generate?? 
    string filename;
    if (this->turn == State::p1) { 
        filename = "sequence1.txt";
    } else {
        filename = "sequence2.txt";
    }
    try { 
        levels *l = this->getGrid()->getPlayer()->getPtrLevel();
        if(l->getRandom() == true) {
            this->readFromFile(filename, l); // outputs a string 
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

Controller::~Controller() {
    delete this->g1;
    delete this->g2;
    delete this->td;
}