#ifndef GRID_H
#define GRID_H
#include <vector>
#include "cell.h"
#include "state.h"
#include "levels.h"
#include "textdisplay.h"
#include "player.h"
#include "block.h"
#include "graphics.h"

/* THE GRID
 * This class is used to store all the information regarding 
 * the Grid, including notifying the Graphcs & TextDisplay. 
 * Note: A Grid OWN'S its player (1-1). The grid does 
 * not know which player it has (player 1 or player 2), and hence
 * accepts a state when called by the controller for anything 
 * that notifies grapics or TextDisplay. The grid also owns 
 * 198 cells in it's theGrid vector. 
 */

class Grid { 
    std::shared_ptr <Player> p = nullptr;
    bool text;
    std::shared_ptr <TextDisplay> td = nullptr; // to add TextDisplay
    int counter = 0; // # of turns since clear
    std::shared_ptr <Graphics> gr = nullptr; //  to add Graphics
    std::vector<std::vector<Cell>> theGrid;
    // vector of vectors of rows of cells 
    public: 
    void init(std::shared_ptr<Player> p, bool text);
    std::shared_ptr<Player> getPlayer();
    friend std::ostream &operator<<(std::ostream &out, const Grid &gr);
    // for output
    void clear(State p, int row, int col);
    int rowclear(State p); // clears any full row 
    bool checkEmpty(int x, int y, std::vector <std::pair<int, int>> coords);
    void score(int n, int level);
    void update(State p);
    void changeBlock(State p, std::shared_ptr<Block> b);
    void setTD(std::shared_ptr<TextDisplay> td);
    void setGraphics(std::shared_ptr<Graphics> gr);
    // where s is the player, n is the # of rows, level is the level of the player
    bool isRowFull(int n); // n is the row you want to check
    bool move(State p, int dir);
    bool validate(int x, int y);
    void reprint(State p, std::vector <std::pair<int, int>> coords, 
    std::vector <std::pair<int, int>> newCoords, char c);
    void fixBlind(State p);
    void rotate(State p);
    void brown(State p, int n);
    bool drop(State p);
    int down(State p);
    ~Grid() = default;
};
#endif
