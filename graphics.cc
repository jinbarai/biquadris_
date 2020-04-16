#include "graphics.h"
using namespace std;

Graphics::Graphics(Player *p1, Player *p2) : p1{p1}, p2{p2} {
    this->xw.fillRectangle(0, 0, 500, 500, 0);
        //"lucidasans-bold-24"
    this->xw.drawStringFont(30, 27, "CS246::BIQUADRIS", "lucidasanstypewriter-bold-24");
    this->xw.drawStringFont(350, 20, "Jagrit, Jin & Kimia", "lucidasans-14");
    this->xw.drawStringFont(30, 47, "Player 1: " + p1->getName(), "lucidasans-18");
    this->xw.drawStringFont(260, 47, "Player 2: "  + p2->getName(), "lucidasans-18");
    string l1;
    string l2;
    stringstream ls1;
    ls1 << p1->getLevel();
    l1 = ls1.str();
    stringstream ls2;
    ls2 << p2->getLevel();
    l2 = ls2.str();
    this->xw.drawStringFont(30, 65, "Level: " + l1, "lucidasans-14");
    this->xw.drawStringFont(260, 65, "Level: " + l2, "lucidasans-14");
    string s1;
    string s2;
    stringstream ss1;
    ss1 << p1->getScore();
    s1 = ss1.str();
    stringstream ss2;
    ss2 << p2->getScore();
    s2 = ss2.str();
    this->xw.drawStringFont(30, 80, "Score: " + s1, "lucidasans-14");
    this->xw.drawStringFont(260, 80, "Score: " + s2, "lucidasans-14");
    this->xw.fillRectangle(30, 90, 209, 360, Xwindow::Black);
    this->xw.fillRectangle(260, 90, 209, 360, Xwindow::Black);
    // can draw lines if you change the rectange colour 
    this->xw.drawLine(30, 90, 239, 90);
    this->xw.drawLine(30, 90, 30, 447);
    this->xw.drawLine(239, 90, 239, 447);
    this->xw.drawLine(30, 447, 239, 447);
}


int Graphics::getColour(char c) {
    if (c == ' ') {
        return Xwindow::Black;
    } else if (c == 'O') {
        return Xwindow::Red;
    } else if (c == 'I') {
        return Xwindow::Orange;
    } else if (c == 'T') {
        return Xwindow::Yellow;
    } else if (c == 'S') {
        return Xwindow::Cyan;
    } else if (c == 'L') {
        return Xwindow::Magenta;
    } else if (c == 'Z') {
        return Xwindow::Green;
    } else if (c == '*') { 
        return Xwindow::Brown;
    } else { // J Block 
        return Xwindow::Blue;
    }
}

void Graphics::notify(State p, int row, int col, char c) {
    row = 17 - row;
    int x; 
    int y =  90 + row * 20;
    if  (p == State::p1) {
        x = 30 + col * 19;
    } else { 
        x = 260 + col * 19;
    }
    int colour = getColour(c);
    this->xw.fillRectangle(x+1, y+1, 17, 18, colour);
}

void Graphics::notifyScore() {
    string s1;
    string s2;
    stringstream ss1;
    ss1 << p1->getScore();
    s1 = ss1.str();
    stringstream ss2;
    ss2 << p2->getScore();
    s2 = ss2.str();
    this->xw.fillRectangle(30, 65, 200, 15, Xwindow::White);
    this->xw.fillRectangle(260, 65, 200, 15, Xwindow::White);
    this->xw.drawStringFont(30, 80, "Score: " + s1, "lucidasans-14");
    this->xw.drawStringFont(260, 80, "Score: " + s2, "lucidasans-14");
}

void Graphics::changeLevel() { 
    string l1;
    string l2;
    stringstream ls1;
    ls1 << p1->getLevel();
    l1 = ls1.str();
    stringstream ls2;
    ls2 << p2->getLevel();
    l2 = ls2.str();
    this->xw.fillRectangle(30, 50, 200, 15, Xwindow::White);
    this->xw.fillRectangle(260, 50, 200, 15, Xwindow::White);
    this->xw.drawStringFont(30, 65, "Level: " + l1, "lucidasans-14");
    this->xw.drawStringFont(260, 65, "Level: " + l2, "lucidasans-14");
}
