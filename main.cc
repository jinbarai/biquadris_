#include "cell.h"
#include "levels.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "grid.h"
#include "textdisplay.h"
#include "block.h"
#include "iblock.h"
#include "controller.h"
#include "player.h"
#include <string>
#include <iostream>
using namespace std;

int main() { 
    string s1;
    string s2;
    cout << "Please enter player 1's name (up to 5 characters)" << endl;
    if (!(cin >> s1)) { 
        return 0;
    }
    while (s1.length() > 5) {
        cout << "Please enter player 1's name (up to 5 characters)" << endl;
        if (!(cin >> s1)) {
            return 0;
        }
    }
    cout << "Please enter player 2's name (up  to 5 characters)" << endl;
    if (!(cin >> s2)) {
        return 0;
    }
    while (s2.length() > 5) {
        cout << "Please enter player 2's name (up  to 5 characters)" << endl;
        if (!(cin >> s2)) {
            return 0;
        }
    }
    Player *p1 = new Player{0, s1, 0};
    Player *p2 = new Player{0, s2, 0};
    Grid *gr = new Grid();
    gr->init(p1, p2);
    Controller c(gr);
    return 0;
}
