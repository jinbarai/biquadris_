#ifndef _COMMAND_
#define _COMMAND_
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Command{
    std::string levelupfile = "textFiles/possible_levelu.txt";
    std::string leveldownfile = "textFiles/possible_leveld.txt";
    std::string leftfile = "textFiles/possible_left.txt";
    std::string rightfile = "textFiles/possible_right.txt";
    std::string downfile = "textFiles/possible_down.txt";
    std::string dropfile = "textFiles/possible_drop.txt";
    std::string clockwisefile = "textFiles/possible_clockwise.txt";
    std::string counterfile = "textFiles/possible_counter.txt";
    std::string restartfile = "textFiles/possible_restart.txt";
    std::string hintfile = "textFiles/possible_hint.txt";
    std::string norandomfile = "textFiles/possible_norandom.txt";
    std::string randomfile = "textFiles/possible_random.txt";
    std::string sequencefile = "textFiles/possible_sequence.txt";
    std::vector <std::string> clockwiseVector;
    std::vector <std::string> counterVector;
    std::vector <std::string> downVector;
    std::vector <std::string> dropVector;   
    std::vector <std::string> leftVector;
    std::vector <std::string> levelupVector;
    std::vector <std::string> leveldownVector;
    std::vector <std::string> norandomVector;
    std::vector <std::string> randomVector;
    std::vector <std::string> restartVector;
    std::vector <std::string> rightVector;
    std::vector <std::string> sequenceVector;
    std::string file;
    std::string oldName = ""; // for rename
    std::string newName = ""; // for rename
    public:
        std::vector <std::string> seq_comm; 
        bool readSeq = false;
        std::string getCommand(std::string);
        void readFiles();
        bool rename();
        std::string extractString(std::string);
        std::string getFile();
        std::string getOldName();
        std::string getNewName();
        bool validNewName();
        void setFile(std::string);
        int getNum(std::string);
        bool isCoreCommand();
        bool fileValid(std::string filename); 
        bool checkinVector(std::string, std::vector <std::string>&);
        ~Command() = default;
};
#endif
