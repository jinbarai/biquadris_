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
#include "levelfive.h"
#include "levelsix.h"
#include "graphics.h"
#include <cstdlib>

const string levelupfile = "possible_levelu.txt";
const string leveldownfile = "possible_leveld.txt";
const string startfile = "possible_start.txt";
const string leftfile = "possible_left.txt";
const string rightfile = "possible_right.txt";
const string downfile = "possible_down.txt";
const string dropfile = "possible_drop.txt";
const string clockwisefile = "possible_clockwise.txt";
const string counterfile = "possible_counter.txt";
const string restartfile = "possible_restart.txt";
const string hintfile = "possible_hint.txt";
const string norandomfile = "possible_norandom.txt";
const string randomfile = "possible_random.txt";

using namespace std;

char getNum(string n)
{
    for (int i = 0; i < n.length(); i++)
    {
        if (isdigit(n[i]))
        {
            return n[i];
        }
    }
}

string extractString(string n)
{
    string extract;
    for (int i = 0; i < n.length(); i++)
    {
        if (isalpha(n[i]))
        {
            n[i] = tolower(n[i]);
            extract = extract + n[i];
        }
    }
    return extract;
}

bool checkinFile(string file, string word)
{
    ifstream name{file};
    string check;
    while (getline(name, check))
    {
        if (word == check)
        {
            return true;
        }
    }
    return false;
}

string getCommand(string n)
{
    string cmd = extractString(n);

    if (checkinFile(startfile, cmd))
    {
        return "start";
    }
    else if (checkinFile(leftfile, cmd))
    {
        return "left";
    }
    else if (checkinFile(rightfile, cmd))
    {
        return "right";
    }
    else if (checkinFile(downfile, cmd))
    {
        return "down";
    }
    else if (checkinFile(dropfile, cmd))
    {
        return "drop";
    }
    else if (checkinFile(clockwisefile, cmd))
    {
        return "cw";
    }
    else if (checkinFile(counterfile, cmd))
    {
        return "ccw";
    }
    else if (checkinFile(restartfile, cmd))
    {
        return "restart";
    }
    else if (checkinFile(hintfile, cmd))
    {
        return "hint";
    }
    else if (checkinFile(randomfile, cmd))
    {
        return "random";
    }
    else if (checkinFile(norandomfile, cmd))
    {
        return "norandom";
    }
    else if (checkinFile(levelupfile, cmd))
    {
        return "levelup";
    }
    else if (checkinFile(leveldownfile, cmd))
    {
        return "leveldown";
    }
    else if (cmd=="end") {
        return cmd; 
    }
    else 
    {
        return "notvalid";
    }
}



int main(int argc, char *argv[])
{   
    cin.exceptions(ios::eofbit | ios::failbit); // from a4q4 main
    string cmd;                                 // for later commands
    string s1;
    string s2;
    cout << "Please enter player 1's name (up to 5 characters)" << endl;
    if (!(cin >> s1))
    {
        return 0;
    }
    if (s1.length() > 5)
    {
        s1 = s1.substr(0, 5);
    }
    cout << "Please enter player 2's name (up to 5 characters)" << endl;
    if (!(cin >> s2))
    {
        return 0;
    }
    if (s2.length() > 5)
    {
        s2 = s2.substr(0, 5);
    }
    cout << "Welcome to Biquadris " << s1 << " and " << s2 << "!" << endl;
    Player *p1 = new Player(0, s1, 0);
    Player *p2 = new Player(0, s2, 0);
    Grid *g1 = new Grid;
    Grid *g2 = new Grid;
    g1->init(p1);
    g2->init(p2);
    TextDisplay *td =  new TextDisplay{p1, p2};    
    Graphics *gr = new Graphics{p1, p2};

    g1->setTD(td);
    g1->setGraphics(gr);
    g2->setTD(td);
    g2->setGraphics(gr);
    Controller c(g1, g2, td);
    cin.ignore();
    cin.clear();
    string command;

    try
    {
        while (true)
        {
            getline(cin,cmd);
            command = getCommand(cmd);
            char num = getNum(cmd);

            if ((command).compare("end")== 0)
            {   
                system("clear");
                cout << "Thank you for playing with us! <3" << endl;
                cout << "Player 1: " << p1->getScore() << endl;
                cout << "Player 2: " << p2->getScore() << endl;
                break;
            }

            int no;
            if (isdigit(num))
            {
                no = stoi(string(1, num));
            }
            else
            {
                if (command == "start")
                {
                    no = 0;
                }
                else
                {
                    no = 1;
                }
            }
            
            if (command == "start")
            {
                if (no != 0)
                {
                    c.startlevel(no);
                }
                c.generate();
                continue;
            }
            else if (command == "left")
            {
                c.move(no, LEFT);
            }
            else if (command == "right")
            {
                c.move(no, RIGHT);
            }
            else if (command == "down")
            {
                c.down(no);
            }
            else if (command == "drop")
            {
                c.drop();
            }
            else if (command == "cw")
            {
                c.cw(no); 
            }
            else if (command == "ccw")
            {
                c.ccw(no);
            }
            else if (command == "random")
            {
                try {
                    c.random(); 
                    c.generate(); 
                }
                catch (string &message) {
                    cout << message << endl; 
                    // Allow user to continue 
                }
                
            }
            else if (command == "restart")
            {
                c.restart(); 
            }
            else if (command == "norandom")
            {
                try {
                    c.norandom(); 
                    c.generate(); 
                }
                catch (string &message) {
                    cout << message << endl; 
                    // Allow user to continue input 
                }
               
            }
            else if (command == "levelup") {
                c.levelup();
            }
            else if (command == "leveldown") {
                c.leveldown(); 
            }
        }
    }
    catch (GameOver(State p)) {}
    catch (ios::failure &)
    {
        cout << " oh we failed" << endl;
    } // Any I/O failure quits, from a4q4 main
}