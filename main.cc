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
#include <string.h>
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
using namespace std;

const string levelupfile = "textFiles/possible_levelu.txt";
const string leveldownfile = "textFiles/possible_leveld.txt";
const string startfile = "textFiles/possible_start.txt";
const string leftfile = "textFiles/possible_left.txt";
const string rightfile = "textFiles/possible_right.txt";
const string downfile = "textFiles/possible_down.txt";
const string dropfile = "textFiles/possible_drop.txt";
const string clockwisefile = "textFiles/possible_clockwise.txt";
const string counterfile = "textFiles/possible_counter.txt";
const string restartfile = "textFiles/possible_restart.txt";
const string hintfile = "textFiles/possible_hint.txt";
const string norandomfile = "textFiles/possible_norandom.txt";
const string randomfile = "textFiles/possible_random.txt";
string file = ""; 

using namespace std;

string getNum(string n)
{
    string nu;
    for (int i = 0; i < n.length(); i++)
    {
        if (isdigit(n[i]))
        {
            nu = nu + n[i];
        }
    }
    return nu;
}

string extractString(string n)
{
    // Special condition for norandom and seq since they also accept a file argument
    string extract;
    if(n.substr(0,4) == "nora" || n.substr(0,3) == "seq") {
        return n; 
    }
    // This will execute if it is not norandom or seq 
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

    if (checkinFile(leftfile, cmd))
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
    else if (checkinFile(levelupfile, cmd))
    {
        return "levelup";
    }
    else if (checkinFile(leveldownfile, cmd))
    {
        return "leveldown";
    }
    //if cmd is end, norand... or sequence return the whole string 
    else if (cmd.substr(0,8)=="norandom" || cmd.substr(0,8) == "sequence")
    {
        // extract the file name after norandom or sequence word
        for (int i=8; i<cmd.length(); i++) {
            if(cmd[i]==' ') {
                continue;
            }
            else {
                file = file + cmd[i]; 
            }
        }
        return cmd.substr(0,8); 
    }
    else
    {
        return cmd;
    }
}

int main(int argc, char *argv[])
{
    cin.exceptions(ios::eofbit | ios::failbit); // from a4q4 main
    string cmd;                                 // for later commands
    string s1;
    string s2;
    string seqFile1 = "biquadris_sequence1.txt";
    string seqFile2 = "biquadris_sequence2.txt";
    int seed = 0;
    int lvl = 0;
    if (argc > 1)
    {
        if (!strcmp(argv[1], "-text"))
        { //text mode
        }
        else if (!strcmp(argv[1], "-seed"))
        {
            if (argc == 3)
                seed = atoi(argv[2]);
        }
        else if (!strcmp(argv[1], "-scriptfile1"))
        {
            if (argc == 3)
                seqFile1 = argv[2];
        }
        else if (!strcmp(argv[1], "-scriptfile2"))
        {
            if (argc == 3)
                seqFile2 = argv[2];
        }
        else if (!strcmp(argv[1], "-startlevel"))
        {
            if (argc == 3)
                lvl = atoi(argv[2]);
        }
    }

    if (lvl > 6) lvl = 0;

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
    Player *p1 = new Player(0, s1, 0, seqFile1);
    Player *p2 = new Player(0, s2, 0, seqFile2);
    Grid *g1 = new Grid;
    Grid *g2 = new Grid;
    g1->init(p1);
    g2->init(p2);
    TextDisplay *td = new TextDisplay{p1, p2};
    Graphics *gr = new Graphics{p1, p2};
    g1->setTD(td);
    g1->setGraphics(gr);
    g2->setTD(td);
    g2->setGraphics(gr);
    Controller c(g1, g2, td, gr);
    cin.ignore();
    cin.clear();
    string command;

    c.startlevel(lvl);
    c.generate();
    try
    {
        while (true)
        {
            // Extracting a line to work a number and string
            file = ""; 
            getline(cin, cmd);
            command = getCommand(cmd);
            string num = getNum(cmd);
            // Handle filenames
            if ((command).compare("end") == 0)
            {
                // This won't work for windows, will work only for mac
                system("clear");
                // For windows: system("CLS");
                cout << "Thank you for playing with us! <3" << endl;
                cout << "Player 1: " << p1->getScore() << endl;
                cout << "Player 2: " << p2->getScore() << endl;
                break;
            }

            int no;
            if (!(num.empty()))
            {
                no = stoi(num);
            }
            else
            {
                no = 1;
            }

            // Handling commands
            if (command == "left")
            {
                no = (no > 10) ? 10 : no;
                c.move(no, LEFT);
            }
            else if (command == "right")
            {
                no = (no > 10) ? 10 : no;
                cout << no << endl;
                c.move(no, RIGHT);
            }
            else if (command == "down")
            {
                no = (no > 17) ? 17 : no;
                cout << no << endl;
                c.down(no);
            }
            else if (command == "drop")
            {
                c.drop();
            }
            else if (command == "cw")
            {
                // logic for simplifying no
                // no = (no%2
                c.cw(no);
            }
            else if (command == "ccw")
            {
                // logic for simplifying no
                c.ccw(no);
            }
            else if (command == "random")
            {
                c.random();
            }
            else if (command == "restart")
            {
                c.restart();
            }
            else if (command == "norandom")
            {
                // pass in a filename
                if (file!="") c.norandom(file);
                else cout<<"Filename not entered or file not readable" << endl; 
            }
            else if (command == "levelup")
            {
                no = (no > 6) ? 6 : no;
                //cout << no << endl;
                for (int i = 0; i < no; i++)
                {
                    c.levelup();
                }
            }
            else if (command == "leveldown")
            {
                no = (no < 0) ? 0 : no;
                //cout << no << endl;
                for (int i = 0; i < no; i++)
                {
                    if (p1->getLevel() == 0)
                    {
                        break;
                    }
                    c.leveldown();
                }
            }
            else if (command == "sequence") {

            }
            else
            {
                cout << "Invalid Command" << endl;
            }
        }
    }    
    catch (GameOver(State p))
    {   
        cout << "Uhoh, game over!" << endl;
        //cout << "Your score is: " << p->getScore() << endl; 
    }
    catch (ios::failure &)
    {
        // This won't work for windows, will work only for mac
        system("clear");
        // For windows: system("CLS");
        cout << "Thank you for playing with us! <3" << endl;
        cout << "Player 1: " << p1->getScore() << endl;
        cout << "Player 2: " << p2->getScore() << endl;
    }
}