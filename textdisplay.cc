#include "textdisplay.h"
#include <iostream>
using namespace std;

/* TextDisplay::TextDisplay(Player *p1, Player *p2, int score)
 * This is the ctor for TextDisplay, which creates the vectors of
 * char theDisplayp1 and theDisplayp2. 
 */
TextDisplay::TextDisplay(shared_ptr<Player> p1, shared_ptr<Player>p2, 
int score) : p1{p1}, p2{p2}, highscore{score} {
    theDisplayp1.clear();
    theDisplayp2.clear();
    for (int i = 0; i < 18; ++i) { // rows 
        vector<char> c;
        // defaults to making every character empty 
        theDisplayp1.emplace_back(c);
        for (int k = 0; k < 11; ++k) { // col 
            theDisplayp1.at(i).emplace_back(' '); 
            // just a space
        }
    }
    for (int i = 0; i < 18; ++i) { // rows 
        vector<char> c;
        theDisplayp2.emplace_back(c);
        for (int k = 0; k < 11; ++k) { // cols
            theDisplayp2.at(i).emplace_back(' '); 
            // just a space
        }
    }
}

/* TextDisplay::updateScore(int n)
 * This is called by Controller::changeTurn() if a player 
 * changes the highscore. 
 */
void TextDisplay::updateScore(int n) {
    this->highscore = n;
}

/* TextDisplay::notify(State p, int row, int col, char c)
 * updates either p1 or p2's vector of char to display the 
 * correct character/"blocktype" of the cell. 
 */
void TextDisplay::notify(State p, int row, int col, char c) { 
    if (p == State::p1) { 
        theDisplayp1.at(row).at(col) = c;
    } else { 
        theDisplayp2.at(row).at(col) = c;
    }
}

/* overloaded TextDisplay << operator
 * This is used to output the TextDisplay 
 */
ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    // print the names
    // gets the size of P1's name to ensure spacing is correct
    // between the two name's. Player 2's distance doesn't matter
    // beacuse it is not visible. 
    int size = td.p1->getName().length();
    out << "Highscore: " << td.highscore << endl;
    out << "Name: " << td.p1->getName();
    // outputs the correct number of spaces needed to make it
    // appear straight 
    for (int i = size; i < 5; ++i) { 
        out << " ";
    }
    // there are 8 spaces between player 1 and player 2's grids, hence 
    // a forloop of 8 spaces. 
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    out << "Name: " << td.p2->getName() << endl;
    // print the levels
    out << "Level:    " << td.p1->getLevel();
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    out << "Level:    " << td.p2->getLevel() << endl;
    // print the scores
    string s1 = to_string(td.p1->getScore());
    int sizescore1 = s1.length();
    out << "Score:";
    // ensures if player 1's score is > 9 the number of spaces do 
    // not mess up the alignment! 
    for (int i = 0; i < (5 - sizescore1); ++i) { out << ' '; }
    out << td.p1->getScore();
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    string s2 = to_string(td.p2->getScore());
    int sizescore2 = s2.length();
    out << "Score:";
    // ensures beautiful alignment! 
    for (int i = 0; i < (5 - sizescore2); ++i) { out << ' ';}
    out << td.p2->getScore() << endl;
    // prints the top grid borders for both players 
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    for (int i = 0; i < 8; ++i) { out <<  ' '; } 
    // creates the top border
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    out << endl;
     // If a player is under specialAction blind, it will 
     // simply not show the range of columns 3-9 and rows 
     // 3-12 (see Biquadris.pdf from cs246 Winter 2020).
    bool f1 = td.p1->isBlind();
    bool f2 = td.p2->isBlind();
    for (int i = 17; i >= 0; --i) {
        for (int k = 0; k < 11; ++k) {
            if (f1) {
                if ((i >= 2 && i <= 11) && (k >= 2 && k <= 8)) {
                    // if it is blind checks range 
                    out << '?';
                } else {
                    out << td.theDisplayp1.at(i).at(k);   
                }
            }
            else { 
                out << td.theDisplayp1.at(i).at(k);
            }
        }
        for (int i = 0; i < 8; ++i) { out <<  ' '; }
        for (int k = 0; k < 11; ++k) {
            if (f2) {
                if ((i >= 2 && i <= 11) && (k >= 2 && k <= 8)) {
                    // checks the blind range. 
                    out << '?';
                } else {
                    out << td.theDisplayp2.at(i).at(k);   
                }
            }
            else { 
                out << td.theDisplayp2.at(i).at(k);
            }
        }
        out << endl;
    } 
    // thh bottom border of both grids 
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    for (int i = 0; i < 8; ++i) { out <<  ' '; } 
    // creates the bottom border
    for (int i = 0; i < 11; ++i) { out <<  '-'; }
    out << endl;
    // outputs the Next Block underneath the Grid! 
    out << "Next:";
    for (int i = 0; i < 14; ++i) { out <<  ' '; } 
    out << "Next:" << endl;
    // if a p1 nextBlock is not available (means game 
    // just started), will 
    // only print spaces instead! 

    /* NOTE ON BEHAVIOUR! 
     * Each block comes with an output for the top of the block
     * and the bottom to display for NextBlock (to account for 
     * vertical or horizontal spawn). Hence, if the block exists
     * this is called to give back the top or bottom. ELSE, it 
     * prints 11 spaces instead. 
     */ 
    if (td.p1->getNextBlock()) { 
        td.p1->getNextBlock()->printBlock(0);
    } else { 
        for (int i = 0; i < 11; ++i) { out <<  ' '; }
    } 
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    if (td.p2->getNextBlock()) {
        td.p2->getNextBlock()->printBlock(0);
    } else { 
        for (int i = 0; i < 11; ++i) { out <<  ' '; }
    }
    out << endl;
    // checks for player's next Block to ensure valid. 
    if (td.p1->getNextBlock()) { 
        td.p1->getNextBlock()->printBlock(1);
    } else { 
        for (int i = 0; i < 11; ++i) { out <<  ' '; }
    } 
    for (int i = 0; i < 8; ++i) { out <<  ' '; }
    if (td.p2->getNextBlock()) {
        td.p2->getNextBlock()->printBlock(1);
    } else { 
        for (int i = 0; i < 11; ++i) { out <<  ' '; }
    }
    out << endl; // outputs a new line at the end for nice spacing 
    out << endl; // another line to be pretty 
    return out;
}

