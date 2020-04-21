#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "grid.h"
#include "block.h"
#include "levels.h"
#include "graphics.h"
#include "state.h"
// when you cannot spot

class Controller { 
    std::shared_ptr<Grid> g1;
    std::shared_ptr<Grid> g2;
    bool bonus = false;
    bool ActionMode = false;
    int highscore;
    bool text;
    bool keyboard = false;
    std::shared_ptr<TextDisplay> td;
    State turn; //  either p1, or p2
    std::shared_ptr<Graphics> gr = nullptr;
    public: 
    std::shared_ptr<Grid> getGrid();
    Controller(std::shared_ptr<Grid> g1, std::shared_ptr<Grid> g2, std::shared_ptr<TextDisplay> td, 
        int score, bool text, std::shared_ptr<Graphics> gr, bool bonus); 
    // main will make player pointers and pass the grid to the controller. 
    void changeTurn();
    void move(int n, int dir);
    void cw(int n = 1); // clockwise
    void ccw(int n = 1); // counterclockwise
    void levelup();
    void leveldown();
    int getHighScore();
    bool isSpecialAction();
    bool getBonus();
    void changeBonus(bool b);
    std::string getKeyboardCommand();
    // Special Actions
    void specialAction(char c, char b);
    void setSpecialAction(bool b);
    void changeBlock(char c);
    void blind();
    void heavy();
    void force(char c);
    void setKeyboard(bool k);
    void generate();
    std::shared_ptr<Grid> getG1();
    std::shared_ptr<Grid> getG2();
    void startlevel(int n);
    void restart(); 
    void drop(int n = 1);
    void random();
    void clearVector(std::shared_ptr<levels> l);
    void norandom(std::string filename);
    void down(int n = 1);
    void readFromFile(std::string file, std::shared_ptr<levels> l); 
    ~Controller() = default;
};

#endif

