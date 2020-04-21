#include "graphics.h"
using namespace std;

const int align1 = 30;
const int align2 = 260;
const int rowheight = 20;
const int colwidth = 19;
const int xpixel = 17;
const int ypixel = 18;
const int maxgrid = 500;
const int gridwidth = 209;
const int gridheight = 360;
const std::string title = "lucidasanstypewriter-bold-24";
const std::string headings = "lucidasans-18";
const std::string scorefont = "lucidasans-bold-14";
const std::string body = "lucidasans-14";

/* Graphics::Graphics() 
 * Used to construct a white background around the display
 */
Graphics::Graphics() {
    this->xw.fillRectangle(0, 0, maxgrid, maxgrid, Xwindow::White);
}

/* Graphics::init(Player *p1, Player *p2, int score)
 * Used to initalize graphics for Player p1, p2 and display the highscore
 * passed in as parameter score. 
 */
void Graphics::init(shared_ptr<Player> p1, shared_ptr<Player> p2, int score) { 
    this->p1 = p1;
    this->p2 = p2;
    // creates whtie background 
    this->xw.fillRectangle(0, 0, maxgrid, maxgrid, Xwindow::White);
    // creates Biquadris Title
    // JJK = first letter of 3 group members 
    this->xw.drawStringFont(align1, 24, "BIQUADRIS:JJK", title);
    // prints the highscore (top-right corner)
    string highscore = to_string(score);
    this->xw.drawStringFont(380, 20, "HighScore: " + highscore, scorefont);
    // prints the two players with names, p1 at align1, p2 at align2
    this->xw.drawStringFont(align1, 47, "Player 1: " + p1->getName(), headings);
    this->xw.drawStringFont(align2, 47, "Player 2: "  + p2->getName(), headings);
    // prints the two players levels 
    string l1 = to_string (p1->getLevel());
    string l2 = to_string (p2->getLevel());
    this->xw.drawStringFont(align1, 65, "Level: " + l1, body);
    this->xw.drawStringFont(align2, 65, "Level: " + l2, body);
    // prints the two players scores 
    string s1 = to_string (p1->getScore());
    string s2 = to_string (p2->getScore());
    this->xw.drawStringFont(align1, 80, "Score: " + s1, body);
    this->xw.drawStringFont(align2, 80, "Score: " + s2, body);
    // creats the two grid (with dimensions) in black 
    this->xw.fillRectangle(align1, 90, gridwidth, gridheight, Xwindow::Black);
    this->xw.fillRectangle(align2, 90, gridwidth, gridheight, Xwindow::Black);
    // making next block
    string block1 = "Next: ";
    string block2 = "Next: ";
    // generates the space for the NextBlock statement (bottom left) at align 1 
    // for p1 and align2 for player 2. 
    // if the next block exists will generate the full block name
    // otherwise will just display << "Next:"
    if (this->p1->getNextBlock()) {
        block1.push_back(this->p1->getNextBlock()->getType());
        block1 += " Block";
    } else if (this->p2->getNextBlock()) {
        block2.push_back(this->p2->getNextBlock()->getType());
        block2 += " Block";
    }
    this->xw.drawStringFont(align1, 470, block1 , body);
    // draws next block space for p1 
    this->xw.fillRectangle(163, 453, 76 , 40); 
    // height: 19* 4, width: 20 * 2
    this->xw.drawStringFont(align2, 470, block2 , body);
    // draws next block space for p2 
    this->xw.fillRectangle(393, 453, 76 , 40);
}


/* Graphics::changeScore(int score)
 * If the highscore is exceeded mid game, will display 
 * the new highscore. Called from controller. 
 */
void Graphics::changeScore(int score) { 
    this->xw.fillRectangle(370, 10, 180, 25, Xwindow::White);
    string highscore;
    stringstream sscore; 
    sscore << score;
    highscore = sscore.str();
    this->xw.drawStringFont(380, 20, "HighScore: " + highscore, scorefont);
}


/* Graphics::getXwindow()
 * Returns a reference to the Xwindow being used to minimize
 * the memory leakage from Xwindow
 */
Xwindow *Graphics::getXwindow(){
    return &this->xw;
}


/* Graphics::getColour(char c)
 * Returns the appropriate colour for each character/type  
 */
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
    } else if (c == 'J') { 
        return Xwindow::Blue;
    } else { 
        return 0;
    }
}


/* Graphics::drawBlind(State p)
 * If the specialAction blind is called for a player
 * this will be used to draw the graphics 
 */
void Graphics::drawBlind(State p) {
    // has a safety guard to ensure not incorrectly called 
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
            // will draw a black square at the cell's space
            this->notify(p, i, k, '?');
            int row = 17 - i;
            int x; 
            int y = 90 + row * rowheight;
            // gets the appropriate x coordinate to draw the white circle 
            if (p == State::p1) {
                x  = align1 + k * colwidth;
            } else { 
                x = align2 + k * colwidth;
            }
            // draws a white circle at the corresponding coordinate 
            // includes a center point and a diameter, which is xpixel. 
            this->xw.fillCircle(x + 9, y + 10, xpixel, Xwindow::White);
        }
    }
}


/* Graphics::level6(State p)
 * This is used to initalize the "hidden" graphics used during Level6. 
 */
void Graphics::level6(State p) {
    // has a safety check to ensure player is actually on Level 6. 
    if (p == State::p1) {
        if (this->p1->getLevel() != 6) { 
            return;
        } else { 
            this->xw.fillRectangle(align1, 90, gridwidth, gridheight, Xwindow::Black);
        }
    } else if (p == State::p2) {
        if (this->p2->getLevel() != 6) {
            return;
        } else { 
            this->xw.fillRectangle(align2, 90, gridwidth, gridheight, Xwindow::Black);
        }
    }
    // obtains the correct x coordindate based on which player it is 
    int x = 110;
    if (p == State::p2) {
        x = 340;
    }
    // outputs a completely black grid with a white square in the middle saying "DROP".
    this->xw.fillRectangle(x, 230, 50, 50, Xwindow::White); 
    this->xw.drawStringFont(x+5, align2, "DROP", body);
}


/* Graphics::blindnotify(State p, int row, int col, char c)
 * Specifically called by grid.cc when restoring the blind affect
 * after the player's turn is over. Will redraw all the graphics. 
 */
void Graphics::blindnotify(State p, int row, int col, char c) {
    // if it is the first cell called (they are called in order) will print
    // the grid as black again (to be more efficient), rather than individually 
    // drawing each cell as black. 
    if (row == 0 && col == 0) {
        if (p == State::p1) {
            this->xw.fillRectangle(align1, 90, gridwidth, gridheight, Xwindow::Black);
        } else {
            this->xw.fillRectangle(align2, 90, gridwidth, gridheight, Xwindow::Black);
        }
    }
    row = 17 - row;
    int x; 
    int y =  90 + row * rowheight; 
    if  (p == State::p1) {
        x = align1 + col * colwidth;
    } else { 
        x = align2 + col * colwidth;
    }
    int colour = getColour(c);
    // refills the Grid. 
    this->xw.fillRectangle(x+1, y+1, xpixel, ypixel, colour);
}


/* Graphics::notify(State p, int row, int col, char c)
 * Used to notify graphics when a cell moves. 
 */
void Graphics::notify(State p, int row, int col, char c) {
    // if notify is called on level 6, it will return to prevent
    // showing the changes. 
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
    int y =  90 + row * rowheight; 
    // obtains the proper x coordinate depending on which player. 
    if  (p == State::p1) {
        x = align1 + col * colwidth;
    } else { 
        x = align2 + col * colwidth;
    }
    int colour = getColour(c);
    // displays the changes 
    this->xw.fillRectangle(x+1, y+1, xpixel, ypixel, colour);
}

/* Graphics::NextBlockp1(char c)
 * Used to notify graphics to print next block
 * will print centered 
 */
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

/* Graphics::NextBlockp2(char c)
 * Similar to NextBlockp1. Attempts to merge functions into 1 were 
 * not successful (far too many variables) 
 */
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

/* Graphics::next()
 * Prints both next blocks
 */
void Graphics::next() {
    // reset to Black
    string block1 = "Next: ";
    string block2 = "Next: ";
    // updates string to cover old next statement 
    if (this->p1->getNextBlock()) {
        this->xw.fillRectangle(30, 450, 200, 50, Xwindow::White);
        block1.push_back(this->p1->getNextBlock()->getType());
        block1 += " Block";
        // obtains the type of the netc block 
        char c1 = this->p1->getNextBlock()->getType();
        this->xw.drawStringFont(align2, 470, block1 , body);
        this->xw.fillRectangle(163, 453, 76 , 40); 
        this->NextBlockp1(c1);
    } 
    if  (this->p2->getNextBlock())  {
        this->xw.fillRectangle(align2, 450, 200, 50, Xwindow::White);
        block2.push_back(this->p2->getNextBlock()->getType());
        block2 += " Block";
        char c2 = this->p2->getNextBlock()->getType();
        this->xw.drawStringFont(260, 470, block2 , body);
        // height: 19* 4, width: 20 * 2
        this->xw.fillRectangle(393, 453, 76 , 40);
        this->NextBlockp2(c2);
    }
}

/* Graphics::notifyScore() 
 * this is used to update the score of the players, 
 * called after a player updates their score 
 */
void Graphics::notifyScore() {
    string s1 = to_string(p1->getScore());
    string s2 = to_string(p2->getScore());
    this->xw.fillRectangle(align1, 65, 200, 15, Xwindow::White);
    this->xw.fillRectangle(align2, 65, 200, 15, Xwindow::White);
    this->xw.drawStringFont(align1, 80, "Score: " + s1, body);
    this->xw.drawStringFont(align2, 80, "Score: " + s2, body);
}

/* Graphics::changeLevel()
 * this is used to update the level of the players, 
 * called after a player updates their level
 */
void Graphics::changeLevel() { 
    string l1 = to_string(p1->getLevel());
    string l2 = to_string(p2->getLevel());
    this->xw.fillRectangle(align1, 50, 200, 15, Xwindow::White);
    this->xw.fillRectangle(align2, 50, 200, 15, Xwindow::White);
    this->xw.drawStringFont(align1, 65, "Level: " + l1, body);
    this->xw.drawStringFont(align2, 65, "Level: " + l2, body);
}



