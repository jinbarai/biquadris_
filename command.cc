#include "command.h"

using namespace std;

string Command::extractString(string n)
{
    string extract;
    if(n.substr(0,1) == "n" || n.substr(0,2) == "se" || n.substr(0,6) == "rename") {
        return n; 
    }
    // This will execute if it is not norandom or seq or rename
    int len = n.length();
    for (int i = 0; i < len; i++)
    {
        if (isalpha(n[i]))
        {
            n[i] = tolower(n[i]);
            extract = extract + n[i];
        }
    }
    return extract;
}

bool Command::checkinVector(string word, vector<string>& lines)
{
    // will go through and check the corresponding name
    // will see if the file exists
    int size = lines.size();
    for (int i = 0; i < size; i++){
        if (lines[i] == word){
            return true;
        }
    }
    return false;
}

int Command::getNum(string n)
{
    string nu = "";
    int num;
    int len = n.length();
    for (int i = 0; i < len; i++)
    {
        if (isdigit(n[i]))
        {
            nu = nu + n[i];
        }
    }
    if (nu == "")
        return 0;
    istringstream(nu) >> num;
    return num;
}

static void readFile(vector<string>& v, string filename){
    // Can't do a getline here because in sequence file the same line could 
    // have different commands like dr dr dr dr
    string line;
    ifstream file{filename};
	while(file>>line) {
                v.emplace_back(line); 
        }
    /*
    while (getline(file, line))
	{
		if(line.size() > 0)
			v.emplace_back(line);
	}*/
}

static bool replace(vector<string>& v, string old, string newName){
    int size = v.size();
    for (int i = 0; i < size; ++i){
        if (v[i] == old){
            v[i] = newName;
            return true;
        }
    }
    return false;
}

bool Command::isCoreCommand(){
    if (this->oldName == "left") return true;
    if (this->oldName == "right") return true;
    if (this->oldName == "down") return true;
    if (this->oldName == "clockwise") return true;
    if (this->oldName == "counterclockwise") return true;
    if (this->oldName == "drop") return true;
    if (this->oldName == "levelup") return true;
    if (this->oldName == "leveldown") return true;
    if (this->oldName == "norandom") return true;
    if (this->oldName == "random") return true;
    if (this->oldName == "sequence") return true;
    if (this->oldName == "restart") return true;
    if (this->oldName == "rename") return true;
    return false;
}

bool Command::rename(){
    if (!validNewName()) {
        cout << "Invalid rename, " << this->newName <<" already exists" << endl;
        return false;
    }
    if (checkinVector(this->oldName, this->levelupVector)){
        return replace(this->levelupVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->leveldownVector)){
        return replace(this->leveldownVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->leftVector)){
        return replace(this->leftVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->rightVector)){
        return replace(this->rightVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->clockwiseVector)){
        return replace(this->clockwiseVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->counterVector)){
        return replace(this->counterVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->downVector)){
        return replace(this->downVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->dropVector)){
        return replace(this->dropVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->norandomVector)){
        return replace(this->norandomVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->randomVector)){
        return replace(this->randomVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->restartVector)){
        return replace(this->restartVector, this->oldName, this->newName);
    } else if (checkinVector(this->oldName, this->sequenceVector)){
        return replace(this->sequenceVector, this->oldName, this->newName);
    } 
    return false;
}

void Command::readFiles(){
    string line;
    readFile(this->levelupVector, this->levelupfile);
    readFile(this->leveldownVector, this->leveldownfile);
    readFile(this->leftVector, this->leftfile);
    readFile(this->rightVector, this->rightfile);
    readFile(this->clockwiseVector, this->clockwisefile);
    readFile(this->counterVector, this->counterfile);
    readFile(this->downVector, this->downfile);
    readFile(this->dropVector, this->dropfile);
    readFile(this->norandomVector, this->norandomfile);
    readFile(this->randomVector, this->randomfile);    
    readFile(this->restartVector, this->restartfile);
    readFile(this->sequenceVector, this->sequencefile);
}

string Command::getFile(){
    return this->file;
}

bool Command::fileValid(string filename) {
    if (filename=="") { return false; }
    ifstream file{filename};
    return (file.good()); 
}

void Command::setFile(string s){
    this->file = s;
}

string Command::getOldName(){
    return this->oldName;
}
string Command::getNewName(){
    return this->newName;
}

bool Command::validNewName(){
    if (checkinVector(this->newName, this->leftVector)) return false;
    if (checkinVector(this->newName, this->rightVector)) return false;
    if (checkinVector(this->newName, this->clockwiseVector)) return false;
    if (checkinVector(this->newName, this->counterVector)) return false;
    if (checkinVector(this->newName, this->downVector)) return false;
    if (checkinVector(this->newName, this->dropVector)) return false;
    if (checkinVector(this->newName, this->rightVector)) return false;
    if (checkinVector(this->newName, this->levelupVector)) return false;
    if (checkinVector(this->newName, this->leveldownVector)) return false;
    if (checkinVector(this->newName, this->norandomVector)) return false;
    if (checkinVector(this->newName, this->randomVector)) return false;
    if (checkinVector(this->newName, this->restartVector)) return false;
    if (checkinVector(this->newName, this->sequenceVector)) return false;
    return true;
}

string Command::getCommand(string n)
{
    /* 
     * used to obtain the commands 
     * from the string constants 
     * to ensure that short form and other
     * forms of the commands can be used 
     */
    string cmd;
   
    cmd = extractString(n);
    if (checkinVector(cmd, this->leftVector))
    {
        return "left";
    }
    else if (checkinVector(cmd, this->rightVector))
    {
        return "right";
    }
    else if (checkinVector(cmd, this->downVector))
    {
        return "down";
    }
    else if (checkinVector(cmd, this->dropVector))
    {
        return "drop";
    }
    else if (checkinVector(cmd, this->clockwiseVector))
    {
        return "clockwise";
    }
    else if (checkinVector(cmd, this->counterVector))
    {
        return "counterclockwise";
    }
    else if (checkinVector(cmd, this->restartVector))
    {
        return "restart";
    }
    else if (checkinVector(cmd, this->randomVector))
    {
        return "random";
    }
    else if (checkinVector(cmd, this->levelupVector))
    {
        return "levelup";
    }
    else if (checkinVector(cmd, this->leveldownVector))
    {
        return "leveldown";
    }
    
    string firstcmd = "";
    int i = 0;
    int len = cmd.length();
    for (; i < len; ++i){
        if (cmd[i] == ' ') break;
        firstcmd += cmd[i];
    }
    
    if (checkinVector(firstcmd, this->norandomVector)){ 
        if (firstcmd == cmd) { return "sos"; }
        file = cmd.substr(i+1, cmd.length());
        return "norandom";
    }

    //else 
    if (checkinVector(firstcmd, this->sequenceVector)){
        if (firstcmd == cmd) { return "sos"; }
        file = cmd.substr(i+1, cmd.length());
        return "sequence";
    }
    //if cmd is end, norand... or sequence return the whole string 
    else if (cmd.substr(0,6) == "rename"){
        this->oldName = "";
        this->newName = "";
        int j = 7;
        int len = cmd.length();
        for (; j < len; ++j){
            if (cmd[j] == ' ') break;
            this->oldName += cmd[j];
        }
        ++j;

        for (;j < len; ++j){
            this->newName += cmd[j];
        }
        return "rename";
    }
    else
    {
        return cmd;
    }
}

