#include "grid.h"
#include "block.h"
#include "controller.h"
#include "player.h"
#include "graphics.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

/* 
 * WELCOME TO BIQUADRIS!! 
 * these strings are saved for simplicity within the 
 * command simplifier getCommand function. 
 */ 
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
#undef _KEYBOARDMODE_
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
    // will go through and check the corresponding name
    // will see if the file exists 
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

int readHighScore(){
    /*
     *used to read the high score from the 
     * file used to save the graphics 
     * obtains information from highscore.txt 
    */
    ifstream file{"highscore.txt"};
    int h;
    file >> h;
    return h;
}

void saveHighScore(int n){
    /* 
     * will save the highscore if it is exceeded 
     * in run of the executable 
     * saves to file highscore.txt found in the repository 
     */
    ofstream file{"highscore.txt"};
    file << n;
}

string getCommand(string n)
{
    /* 
     * used to obtain the commands 
     * from the string constants 
     * to ensure that short form and other
     * forms of the commands can be used 
     */
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
    bool keyboardmode = false; 
    /* this bool is 
     * used for extra commad -keyboardmode 
     * where arrows can be used to play 
     */
    cin.exceptions(ios::eofbit | ios::failbit); // from a4q4 main
    string cmd;                                 // for later commands
    string s1; // used to check for player 1's name 
    string s2; // used to check for player 2's name 
    int highScore = readHighScore();
    // default string names if no other strings are provided 
    string seqFile1 = "biquadris_sequence1.txt";
    string seqFile2 = "biquadris_sequence2.txt";
    unsigned int seed=0;
    bool text = false; // used if text command is supplied to the program 
    int lvl = 0; // used if a particular level is supplied to the program 
    if (argc > 1)
    {
        /* 
         * this if statement is used to check for the command line flgas
         * passed to the program 
         */ 
        if (!strcmp(argv[1],"-text")) // if text is provided 
        { 
            text = true;
        }
        else if (!strcmp(argv[1], "-seed")) // if seed is provided 
        {
            if (argc == 3) seed = atoi(argv[2]);
            srand(seed);
        }
        else if (!strcmp(argv[1], "-scriptfile1")) // if scriptfiles are provided 
        {
            if (argc == 3)
                seqFile1 = argv[2];
        }
        else if (!strcmp(argv[1], "-scriptfile2"))
        {
            if (argc == 3)
                seqFile2 = argv[2];
        }
        else if (!strcmp(argv[1], "-startlevel")) // to start at a particular level
        {
            if (argc == 3)
                lvl = atoi(argv[2]);
        }
        else if (!strcmp(argv[1], "-keyboardmode")){ // to start keyboard mode 
           keyboardmode = true;
        }
    }

    if (lvl > 6) lvl = 0;
    // to determine Player 1's name 
    cout << "Please enter player 1's name (up to 5 characters)" << endl;
    if (!(cin >> s1))
    {
        return 0;
    }
    if (s1.length() > 5)
    {
        s1 = s1.substr(0, 5);
    }
    // to determine Player 2's name 
    cout << "Please enter player 2's name (up to 5 characters)" << endl;
    /* 
     * Player names are to be 5 characters (or less) to ensure 
     * a "pretty" display spacing. Anything over 5 characters will 
     * be cut to be exactly 5 characters. 
     */
    if (!(cin >> s2))
    {
        return 0;
    }
    if (s2.length() > 5) // ensures stringlength <= 5
    {
        s2 = s2.substr(0, 5);
    }
    cout << "Welcome to Biquadris " << s1 << " and " << s2 << "!" << endl;
    // make the pointers for player 1 and 2 
    shared_ptr<Player> p1 = make_shared<Player>(0, s1, 0, seqFile1);
    shared_ptr<Player> p2 = make_shared<Player>(0, s2, 0, seqFile2);
    // will make Grid pointers to be passed to the controller
    // upon it's construction 
    auto g1 = make_shared<Grid>();
    auto g2 = make_shared<Grid>();
    // used to initalie the Grid 
    g1->init(p1, text);
    g2->init(p2, text);
    shared_ptr<TextDisplay> td = make_shared<TextDisplay>(p1, p2, 0); // given the programs highscore!
    g1->setTD(td);
    g2->setTD(td);
    shared_ptr<Graphics> gr;
    /* 
     * if the program is in text Mode, the graphicis
     * pointer will be set to nullptr, else an proper
     * shared pointer is created  
     */
    if (!text) {
        gr = make_shared<Graphics>(p1, p2, 0);
    } else { 
        gr = nullptr;
    }
    g1->setGraphics(gr);
    g2->setGraphics(gr);
    unique_ptr<Controller> c = make_unique<Controller>(g1, g2, td, 0, text, gr);
    if (keyboardmode) { // to ensure that keyboard mode is properly entered 
        c->setKeyboard(keyboardmode);
    }
    cin.ignore();
    cin.clear();
    string command;
    c->startlevel(lvl); 
    c->generate(); // will start the first turn (defaults to Player 1)
    try
    {
        while (true)
        {
            // Extracting a line to work a number and string
            file = ""; 
            int multiplier = 1;
            if (!keyboardmode){ // if it is keyboard mode
            // other commands are provided 
                getline(cin, cmd); // obtains the line from the user's input 
                // converts to a command 
                command = getCommand(cmd);
                string num = getNum(cmd);

                // Handle filenames
                if ((command).compare("end") == 0)
                {
                    // This won't work for windows, will work only for mac
                //    system("clear");
                    saveHighScore(c->getHighScore());
                    // used to save the highscore 
                    // For windows: system("CLS");
                    cout << "Thank you for playing with us! <3" << endl;
                    cout << "Player 1: " << p1->getScore() << endl;
                    cout << "Player 2: " << p2->getScore() << endl;
                    break;
                }
                if (!(num.empty()))
                    multiplier = stoi(num);
                else
                    multiplier = 1;
            }
            else if (keyboardmode) {
                // used to obtain commands from the corresponding keyboard mode properly 
                command = c->getKeyboardCommand();
            }
            /* 
             * this is where the true game loop begins, 
             * begin to move with the commands
             * if it s provided via keyboard mode, 
             * it will have limited command functionality
             * all commands accept short form , as provided by the 
             * getCommand function 
             */ 
            if (command == "left")
            {
                multiplier = (multiplier > 10) ? 10 : multiplier;
                // will take the move command modulo 10 to 
                // for efficiency 
                c->move(multiplier, LEFT);
            }
            else if (command == "right")
            {
                multiplier = (multiplier > 10) ? 10 : multiplier;
                // will take the modulo (similarly to left)
                c->move(multiplier, RIGHT);
            }
            else if (command == "down")
            {
                multiplier = (multiplier > 17) ? 17 : multiplier;
                // used to save efficiency 
                cout << multiplier << endl;
                c->down(multiplier);
            }
            else if (command == "drop")
            {
                c->drop(multiplier);
            }
            else if (command == "cw")
            {
                // modulo of multipler is created in the controller's
                // cw function 
                // logic for simplifying multiplier
                c->cw(multiplier);
            }
            else if (command == "ccw")
            {
                // similar to cw 
                c->ccw(multiplier);
            }
            else if (command == "random")
            {
                c->random();
            }
            else if (command == "restart")
            {
                c->restart();
            }
            else if (command == "norandom")
            {
                // pass in a filename
                if (file!="") c->norandom(file);
                else cout<<"Filename not entered or file not readable" << endl; 
            }
            else if (command == "levelup")
            {
                multiplier = (multiplier > 6) ? 6 : multiplier;
                for (int i = 0; i < multiplier; i++)
                {
                    if (c->getGrid()->getPlayer()->getLevel() != 6) {
                        c->levelup();
                    }
                    else {
                        break; 
                    }
                }
            }
            else if (command == "leveldown")
            {
                multiplier = (multiplier < 0) ? 0 : multiplier;
                if (c->getGrid()->getPlayer()->getLevel())
                //cout << multiplier << endl;
                for (int i = 0; i < multiplier; i++)
                {
                    // check if player whose turn it is has a level 0 then break
                    if (c->getGrid()->getPlayer()->getLevel() != 0) {
                        c->leveldown();
                    }
                    else {
                        break; 
                    }
                }
            }
            else if (command == "sequence") {
                 // pass in a filename
                if (file!="") c->norandom(file);
                else cout<<"Filename not entered or file not readable" << endl;
            }
            else if (command  == "i" || command  == "j" || 
                command  == "l" || command  == "o" || 
                command  == "z" || command  == "s" || command  == "t") {
                /* this command is used to change the block to 
                 * another block provided by the user
                 * may produce output if the block can not be changed
                 * because of the grid's bounds [11x18]
                 */
                char com = command[0];
                c->changeBlock(com);
            }
            else {}
        }
    }    
    catch (GameOver g)
    {   
        cout << "GAME OVER!" << endl;
        // will determine which player won the game 
        // as it will be the opposite player who threw the GameOver class
        // if Player 1 -> Player 2 wins
        // if Player 2 -> Player 1 wins 
        if (g.player == State::p1) { 
            cout << "Player 2: " << c->getG2()->getPlayer()->getName() << " wins!" << endl;
        } else { 
            cout << "Player 1: " << c->getG1()->getPlayer()->getName() << " wins!" << endl;
        } 
    }
    catch (ios::failure &)
    {
        // This won't work for windows, will work only for mac
        //system("clear");
        cout << "Thank you for playing with us! <3" << endl;
        cout << "Player 1: " << p1->getScore() << endl;
        cout << "Player 2: " << p2->getScore() << endl;
        // will provide the scores of both players 
    }
}