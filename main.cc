#include "levels.h"
#include "grid.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "oblock.h"
#include "lblock.h"
#include "tblock.h"
#include "zblock.h"
#include "sblock.h"
#include "controller.h"
#include "player.h"
#include <string>
#include <iostream>
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
using namespace std;

int main(int argc, char *argv[]) { 
    cin.exceptions(ios::eofbit|ios::failbit); // from a4q4 main
    string cmd; // for later commands
    string s1;
    string s2;
    cout << "Please enter player 1's name (up to 5 characters)" << endl;
    if (!(cin >> s1)) { 
        return 0;
    } if (s1.length() > 5) {
        s1 = s1.substr(0,5);
    }
    cout << "Please enter player 2's name (up to 5 characters)" << endl;
    if (!(cin >> s2)) {
        return 0;
    }
    if (s2.length() > 5) { 
        s2 = s2.substr(0,5);
    }
    cout << "Welcome to Biquadris " << s1 << " and " << s2 << "!" << endl;
    Player *p1 = new Player(0, s1, 0);
    Player *p2 = new Player(0, s2, 0);
    Grid *g1 = new Grid(p1);
    Grid *g2 = new Grid(p2);
    TextDisplay *td =  new TextDisplay{p1, p2};
    g1->setTD(td);
    g2->setTD(td);
    Controller c(g1, g2);
    try { 
        while(true) { 
            cin >> cmd;
            if (cmd == "startlevel" || cmd == "starlevel" || cmd == "starlevle" || 
            cmd == "start level" || cmd == "startlevle" || cmd == "startl" || cmd == "sl") { 
                int n = 0;
                cin >> n;
                c.startlevel(n);
                c.generate();
            } else if (cmd == "start" || cmd == "s") { 
                c.generate();
                continue;
            } else if (cmd == "left" || cmd == "lef") {
                c.move(1, LEFT);
            } else if (cmd == "right" || cmd == "ri" || cmd == "rig" || cmd == "righ") {
                c.move(1, RIGHT);
            }
            if (false) { // write later
                // for special commands 
            }
        }
    } 
    catch (ios::failure &) {}  // Any I/O failure quits, from a4q4 main
}

