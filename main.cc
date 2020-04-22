#include "grid.h"
#include "block.h"
#include "controller.h"
#include "player.h"
#include "graphics.h"
#include <algorithm>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "command.h"
using namespace std;

/* 
 * WELCOME TO BIQUADRIS!! 
 * these strings are saved for simplicity within the 
 * command simplifier getCommand function. 
 */ 

using namespace std;

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



int main(int argc, char *argv[])
{
    bool keyboardmode = false; 
 
    /* used for extra commad -keyboardmode 
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
    unsigned int seed = 0;
    bool text = false; // used if text command is supplied to the program 
    int lvl = 0; // used if a particular level is supplied to the program 
    bool bonus = false;
    /* 
     * this if statement is used to check for the command line flags
     * passed to the program 
     */ 
    for (int i = 0; i < argc ; ++i) { 

        if (!strcmp(argv[i],"-text")) // if text is provided 
        { 
            text = true;
        }
        else if (!strcmp(argv[i], "-bonus")) 
        { 
            bonus = true;
        }
        else if (!strcmp(argv[i], "-seed")) // if seed is provided 
        {
            ++i;
            seed = stoi(argv[i]);
            srand(seed);
        }
        else if (!strcmp(argv[i], "-scriptfile1")) // if scriptfiles are provided 
        {
            ++i;
            seqFile1 = argv[i];
        }
        else if (!strcmp(argv[i], "-scriptfile2"))
        {
            ++i;
            seqFile2 = argv[i];
        }
        else if (!strcmp(argv[i], "-startlevel")) // to start at a particular level
        {
            ++i;
            if (i >= argc) {
                lvl = 0;
            } else { 
                lvl = stoi(argv[i]);
            }
        }
        else if (!strcmp(argv[i], "-keyboardmode")){ // to start keyboard mode 
           keyboardmode = true;
           for (int k = 0; k < argc; ++k) { 
               // -keyboard mode is not compatable with -text mode 
               // will turn keyboardmode off 
               if (!strcmp(argv[k], "-text")) {
                   cout << "-text flag provided, keyboardmode will not be in effect" 
                   << endl;
                   keyboardmode = false;
                   break;
               }
           }
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
    shared_ptr<Player> p1 = make_shared<Player>(s1, 0, bonus, seqFile1);
    shared_ptr<Player> p2 = make_shared<Player>(s2, 0, bonus, seqFile2);
    // will make Grid pointers to be passed to the controller
    // upon it's construction 
    auto g1 = make_shared<Grid>();
    auto g2 = make_shared<Grid>();
    // used to initalie the Grid 
    g1->init(p1, text);
    g2->init(p2, text);
    shared_ptr<TextDisplay> td = make_shared<TextDisplay>(p1, p2, highScore); // given the programs highscore!
    g1->setTD(td);
    g2->setTD(td);
    shared_ptr<Graphics> gr;
    /* 
     * if the program is in text Mode, the graphicis
     * pointer will be set to nullptr, else an proper
     * shared pointer is created  
     */
    if (!text) {
        gr = make_shared<Graphics>();
        gr->init(p1, p2, highScore);
    } else { 
        gr = nullptr;
    }
    g1->setGraphics(gr);
    g2->setGraphics(gr);
    unique_ptr<Controller> c = make_unique<Controller>(g1, g2, td, highScore, text, gr, bonus);
    
    if (keyboardmode) { // to ensure that keyboard mode is properly entered 
        c->setKeyboard(keyboardmode);
    }
    cin.ignore();
    cin.clear();

    string command;
    c->startlevel(lvl); 
    c->generate(); // will start the first turn (defaults to Player 1)
    Command com;
    com.readFiles();
    try
    {
        while (true)
        {
            try { 
            // Extracting a line to work a number and string
            // file = ""; 
            int multiplier = 1;
            if (!keyboardmode) { // if it is keyboard mode
            // other commands are provided 
                if (com.seq_comm.empty()) com.readSeq = false; 
                if(!com.readSeq) {
                    getline(cin, cmd); // obtains the line from the user's input 
                }
                else if(!com.seq_comm.empty() && com.readSeq) {
                    cmd = com.seq_comm.back();
                    com.seq_comm.pop_back();  
                }
                // converts to a command 
                command = com.getCommand(cmd);
                if (command == "sos") {
                    cout << "Filename not entered or file not readable" << endl; 
                    continue; 
                }
                int num = com.getNum(cmd);
                // Handle filenames
                if ((command).compare("end") == 0)
                {
                    saveHighScore(c->getHighScore());
                    cout << "Thank you for playing with us! <3" << endl;
                    int score1 = c->getG1()->getPlayer()->getScore();
                    string name1 = c->getG1()->getPlayer()->getName();
                    int score2 = c->getG2()->getPlayer()->getScore();
                    string name2 = c->getG2()->getPlayer()->getName();
                    cout << "Player 1: " << score1 << endl;
                    cout << "Player 2: " << score2  << endl;
                    if (score1 > score2) {
                        cout << "Player 1: " << name1 << " wins!" << endl;
                    } else if (score1 < score2) { 
                        cout << "Player 2: " << name2 << " wins!" << endl;
                    } else { 
                        cout << "It's a tie!" << endl;
                    }
                    break;
                }
                if (num != 0)
                    multiplier = num;
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
             * if it is provided via keyboard mode, 
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
                //cout << multiplier << endl;
                c->down(multiplier);
            }
            else if (command == "drop")
            {
                c->drop(multiplier);
            }
            else if (command == "clockwise")
            {
                // modulo of multipler is created in the controller's
                // cw function 
                // logic for simplifying multiplier
                c->cw(multiplier);
            }
            else if (command == "counterclockwise")
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
                if (com.fileValid(com.getFile())) {c->norandom(com.getFile());}
                else cout<<"Filename not entered or file not readable" << endl; 
                com.setFile(""); 
            }
            else if (command == "levelup")
            {
                if (bonus) {
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
                } else { 
                    multiplier = (multiplier > 4) ? 4 : multiplier;
                    for (int i = 0; i < multiplier; i++)
                    {
                        if (c->getGrid()->getPlayer()->getLevel() != 4) {
                            c->levelup();
                        }
                        else {
                            break; 
                        }
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
                 //flush the vector 
                com.seq_comm.clear(); 
                 // pass in a filename
                ifstream fname{com.getFile()};
                // check if a file exists or is readable, and open it
                if(fname.good()) {
                    string word; 
                    com.readSeq = true; 
                    while(fname>>word) {
                        com.seq_comm.emplace_back(word); 
                    }
                    reverse(com.seq_comm.begin(),com.seq_comm.end());
                }
                else cout << "Filename not entered or file not readable" << endl;
            }
            else if (command  == "i" || command  == "j" || 
                command  == "l" || command  == "o" || 
                command  == "z" || command  == "s" || command  == "t") {
                /* this command is used to change the block to 
                 * another block provided by the user
                 * may produce output if the block can not be changed
                 * because of the grid's bounds [11x18]
                 */
                char b = command[0];
                c->changeBlock(b);
            }
            else if (bonus && command == "rename"){
                if (com.rename()){
                    if (com.isCoreCommand()){
                        cout << "You attempted to rename a core command. Both words are now valid." << endl;
                    }else{
                        cout << "Success! " << com.getOldName() << " was renamed to ";
                        cout << com.getNewName() << endl;
                    }          
                }
            } else if (command == "bonus") {
                if (bonus == false) {
                    bonus = true;
                    c->changeBonus(bonus);
                    c->getG1()->getPlayer()->changeBonus(bonus);
                    c->getG2()->getPlayer()->changeBonus(bonus);
                } else { 
                    bonus = false;
                    c->changeBonus(bonus);
                    if (c->getG1()->getPlayer()->getLevel() > 4) {
                        c->getG1()->getPlayer()->changeLevel(4);
                        if (!text) { 
                            gr->changeLevel();
                        }
                    }
                    if (c->getG2()->getPlayer()->getLevel() > 4) {
                        c->getG2()->getPlayer()->changeLevel(4);
                        if (!text) { 
                            gr->changeLevel();
                        }
                    }
                }
            }
            else {}
            } catch (SpecialAction p) {
                if (com.seq_comm.empty()) com.readSeq = false; 
                cout << "Congratulations on your Special Action!" << endl;
                string s;
                char action;
                char b = ' ';
                if (!com.readSeq) {
                    cout << "Select one of the following: ";
                    cout << "Blind, Heavy or Force" << endl;
                    cin >> s;
                    action = s.at(0);
                    if (action == 'f' || action == 'F') {
                        cin >> b;
                    }
                } else { 
                    s = com.seq_comm.back(); 
                    com.seq_comm.pop_back();
                    action = s.at(0);
                    if (com.seq_comm.empty()) { 
                        com.readSeq = false; 
                        if (action == 'f' || action == 'F') {
                        cout << "Sequence now empty! Please provide input for the blocktype you would like to Force!" << endl;
                        cin >> b;
                        }
                    }
                    else if (action == 'f' || action == 'F') {
                        string key;
                        key = com.seq_comm.back();
                        b = key.at(0);
                        com.seq_comm.pop_back(); 
                    }
                }
                c->setSpecialAction(false);
                c->specialAction(action, b);
                continue;
            }
        }
    }    
    catch (GameOver g)
    {   
        cout << "GAME OVER!" << endl;
        // will determine which player won the game 
        // as it will be the opposite player who threw the GameOver class
        // if Player 1 -> Player 2 wins
        // if Player 2 -> Player 1 wins 
        if (c->getHighScore() > highScore) {
            saveHighScore(c->getHighScore());
        }
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
        if (c->getHighScore() > highScore) {
            saveHighScore(c->getHighScore());
        }
        cout << "Thank you for playing with us! <3" << endl;
        int score1 = c->getG1()->getPlayer()->getScore();
        string name1 = c->getG1()->getPlayer()->getName();
        int score2 = c->getG2()->getPlayer()->getScore();
        string name2 = c->getG2()->getPlayer()->getName();
        cout << "Player 1: " << score1 << endl;
        cout << "Player 2: " << score2  << endl;
        if (score1 > score2) {
            cout << "Player 1: " << name1 << " wins!" << endl;
        } else if (score1 < score2) { 
            cout << "Player 2: " << name2 << " wins!" << endl;
        } else { 
            cout << "It's a tie!" << endl;
        }
        // will provide the scores of both players 
    }
}