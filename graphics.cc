#include "graphics.h"
using namespace std;

Graphics::Graphics(Player *p1, Player *p2, int score) : p1{p1}, p2{p2} { 
    this->xw.fillRectangle(0, 0, 500, 500, 0);
        //"lucidasans-bold-24"
    this->xw.drawStringFont(30, 24, "BIQUADRIS:JJK", "lucidasanstypewriter-bold-24");
    string highscore;
    stringstream sscore; 
    sscore << score;
    highscore = sscore.str();
    this->xw.drawStringFont(380, 20, "HighScore: " + highscore, "lucidasans-bold-14");
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
    // making next block
    string block1 = "Next: ";
    string block2 = "Next: ";
    if (this->p1->getNextBlock()) {
        block1.push_back(this->p1->getNextBlock()->getType());
        block1 += " Block";
    } else if (this->p2->getNextBlock()) {
        block2.push_back(this->p2->getNextBlock()->getType());
        block2 += " Block";
    }
    this->xw.drawStringFont(30, 470, block1 , "lucidasans-14");
    this->xw.fillRectangle(163, 453, 76 , 40); 
    // height: 19* 4, width: 20 * 2
    this->xw.drawStringFont(260, 470, block2 , "lucidasans-14");
    this->xw.fillRectangle(393, 453, 76 , 40);
}


void Graphics::changeScore(int score) { 
    this->xw.fillRectangle(380, 20, 50, 20, Xwindow::White);
    string highscore;
    stringstream sscore; 
    sscore << score;
    highscore = sscore.str();
    this->xw.drawStringFont(380, 20, "HighScore: " + highscore, "lucidasans-bold-14");
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
    } else if (c == '?') { 
        return Xwindow::Black;
    } else { // J Block 
        return Xwindow::Blue;
    }
}

void Graphics::drawBlind(State p) {
    if (p == State::p1) {
        if (!this->p1->isBlind()) {
            return;
        }
    } else if (p == State::p2) {
        if (!this->p2->isBlind()) {
            return;
        }
    }
    for (int i = 2; i <= 11; ++i) {
        for (int k = 2; k <= 8; ++k) {
            this->notify(p, i, k, '?');
            int row = 17 - i;
            int x; 
            int y = 90 + row  * 20;
            if (p == State::p1) {
                x  = 30 + k * 19;
            } else { 
                x = 260 + k * 19;
            }
            this->xw.fillCircle(x + 9, y + 10, 17, Xwindow::White);
        }
    }
}

void Graphics::level6(State p) {
  if (p == State::p1) {
        if (this->p1->getLevel() != 6) { 
            return;
        } else { 
            this->xw.fillRectangle(30, 90, 209, 360, Xwindow::Black);
        }
    } else if (p == State::p2) {
        if (this->p2->getLevel() != 6) {
            return;
        } else { 
            this->xw.fillRectangle(260, 90, 209, 360, Xwindow::Black);
        }
    }
    int x = 110;
    if (p == State::p2) {
        x = 340;
    }
    this->xw.fillRectangle(x, 230, 50, 50, Xwindow::White); 
    this->xw.drawStringFont(x+5, 260, "DROP", "lucidasans-14");
}

void Graphics::blindnotify(State p, int row, int col, char c) {
    if (row == 0 && col == 0) {
        if (p == State::p1) {
            this->xw.fillRectangle(30, 90, 209, 360, Xwindow::Black);
        } else {
            this->xw.fillRectangle(260, 90, 209, 360, Xwindow::Black);
        }
    }
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

void Graphics::notify(State p, int row, int col, char c) {
    if (p == State::p1) {
        if (this->p1->getLevel() == 6) { 
            return;
        }
    } else if (p == State::p2) {
        if (this->p2->getLevel() == 6) {
            return;
        }
    }
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

void Graphics::NextBlockp1(char c) { 
    int colour = this->getColour(c);
    int x1 = 173;
    int x2 = 192;
    int x3 = 211; 
    if (c == 'O') {
        this->xw.fillRectangle(182 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(182 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(201 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(201 + 1, 473 + 1, 17, 18, colour);
    } else if (c == 'I') {
        this->xw.fillRectangle(163 + 1, 463 + 1, 17, 18, colour);
        this->xw.fillRectangle(182 + 1, 463 + 1, 17, 18, colour);
        this->xw.fillRectangle(201 + 1, 463 + 1, 17, 18, colour);
        this->xw.fillRectangle(220 + 1, 463 + 1, 17, 18, colour);
    } else if (c == 'T') {
        this->xw.fillRectangle(x2 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 473 + 1, 17, 18, colour);
    } else if (c == 'S') {
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 453 + 1, 17, 18, colour);
    } else if (c == 'L') {
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 453 + 1, 17, 18, colour);
    } else if (c == 'Z') {
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 453 + 1, 17, 18, colour);
    } else if (c == 'J') { 
        this->xw.fillRectangle(x1 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 473 + 1, 17, 18, colour);
    }
}

void Graphics::NextBlockp2(char c) { 
      int colour = this->getColour(c);
    int x1 = 403;
    int x2 = 422;
    int x3 = 441; 
    if (c == 'O') {
        this->xw.fillRectangle(412 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(412 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(431 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(431 + 1, 473 + 1, 17, 18, colour);
    } else if (c == 'I') {
        this->xw.fillRectangle(393 + 1, 463 + 1, 17, 18, colour);
        this->xw.fillRectangle(412 + 1, 463 + 1, 17, 18, colour);
        this->xw.fillRectangle(431 + 1, 463 + 1, 17, 18, colour);
        this->xw.fillRectangle(450 + 1, 463 + 1, 17, 18, colour);
    } else if (c == 'T') {
        this->xw.fillRectangle(x2 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 473 + 1, 17, 18, colour);
    } else if (c == 'S') {
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 453 + 1, 17, 18, colour);
    } else if (c == 'L') {
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 453 + 1, 17, 18, colour);
    } else if (c == 'Z') {
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 453 + 1, 17, 18, colour);
    } else if (c == 'J') { 
        this->xw.fillRectangle(x1 + 1, 453 + 1, 17, 18, colour);
        this->xw.fillRectangle(x1 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x2 + 1, 473 + 1, 17, 18, colour);
        this->xw.fillRectangle(x3 + 1, 473 + 1, 17, 18, colour);
    }
}


void Graphics::next() {
    // reset to Black
    string block1 = "Next: ";
    string block2 = "Next: ";
    if (this->p1->getNextBlock()) {
        this->xw.fillRectangle(30, 450, 200, 50, Xwindow::White);
        block1.push_back(this->p1->getNextBlock()->getType());
        block1 += " Block";
        char c1 = this->p1->getNextBlock()->getType();
        this->xw.drawStringFont(30, 470, block1 , "lucidasans-14");
        this->xw.fillRectangle(163, 453, 76 , 40); 
        this->NextBlockp1(c1);
    } 
    if  (this->p2->getNextBlock())  {
        this->xw.fillRectangle(260, 450, 200, 50, Xwindow::White);
        block2.push_back(this->p2->getNextBlock()->getType());
        block2 += " Block";
        char c2 = this->p2->getNextBlock()->getType();
        this->xw.drawStringFont(260, 470, block2 , "lucidasans-14");
        // height: 19* 4, width: 20 * 2
        this->xw.fillRectangle(393, 453, 76 , 40);
        this->NextBlockp2(c2);
    }
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
