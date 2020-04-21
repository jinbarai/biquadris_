#include "grid.h"
#include <iostream>
using namespace std;

/* Grid::init(Player *p, bool text )
 * Instead of a constructor, we have an initalizer, 
 * In order to make the restart command easier. 
 * Hence, whenever init is called, the whole game is cleared
 * Also, a new player is accpeted by the Grid when this happens. 
 */
void Grid::init(shared_ptr<Player> p, bool text) {
    this->theGrid.clear();
    // takes a bool text in order to determine if 
    // graphics should be updated via an Observer 
    // Design pattern 
    this->text = text;
    this->p = p;
    // creates an 11x18 grid 
    for (int i = 0; i < 18; ++i) { // rows
        vector<Cell> c;
        this->theGrid.emplace_back(c);
        for (int k = 0; k < 11; ++k) { // columns 
            this->theGrid.at(i).emplace_back(Cell(i,k,' '));
            // ' ' represents an EMPTY cell 
        }
    }
}

/* Grid::update(State p)
 * Update is used in order to add a block to the grid, at it's 
 * spawning position. A state is taken in in order to pass the 
 * correct player to TextDisplay and Graphics. 
 */
void Grid::update(State p) {
    shared_ptr<Block> b = this->getPlayer()->getBlock();
    // saves the block for cleaner access 
    if (this->getPlayer()->isSpecialHeavy()){ // to determine heavy nature 
        this->getPlayer()->getBlock()->makeCommandHeavy(true);
    }
    // obtains the coords from the block 
    vector <pair <int, int>> coords = b->getCoords();
    char type = b->getType(); 
    for (int i = 0; i < 4; ++i) {
        int x = coords.at(i).first;
        int y = coords.at(i).second;
        // if the coordinates are not valid, 
        // block cannot be dropped and the palyer loses. 
        // thowing GameOver (caught in main.cc)
        if (!validate(x, y)) { 
            throw GameOver{p};
        }
        if (!theGrid.at(y).at(x).isEmpty()) {
            throw GameOver{p}; // means it cannot be dropped 
        }  else { // will continue to print them
            theGrid.at(y).at(x).setType(type);
            this->td->notify(p, y, x, type);
            if (!this->text && this->gr) { // updates graphics
            // if program is not in text mode. 
                this->gr->notify(p, y, x, type);
            }
        }
    }
}

/* Grid::move(State p, int dir)
 * will move the block left and right (one time)
 * in the direction passed in. Directions are defined in block.h
 * where (LEFT = -1), (RIGHT = 1). A validate is done on each 
 * cell before it prints. 
 * A state is taken in in order to pass the correct player to 
 * TextDisplay and Graphics. 
 * Note: a return value of 0 means it did not move. 1 means 
 * a move was successful. 
 */
bool Grid::move(State p, int dir) { 
    shared_ptr<Block> b = this->getPlayer()->getBlock();
    // block and dir come from controller
    vector <pair<int, int>> coords = b->getCoords();
    b->move(dir); // this will update the coordinates on the block 
    vector <pair<int, int>> newcoords = b->getCoords();
    for (int i = 0; i < 4; ++i) {
        // check to make sure new coordinatres are valid 
        int x = newcoords.at(i).first;
        int y = newcoords.at(i).second;
        if (!validate(x, y)) { // ensurse they are valid coordintes
            b->setCoords(coords); // resets prior coordinates 
            return false; // unable to move 
        } 
        if (!this->theGrid.at(y).at(x).isEmpty()) { 
            bool flag = checkEmpty(x, y, coords);
            if (flag == 1) { // the cell wanting to be moved to 
            // does not belong to the old or updated block 
            // (belongs to another block and hence, does not update)
                b->setCoords(coords); // resets prior coordintes 
                return false; // unable to move 
            }
        }
    } 
    char c = b->getType();
    reprint(p, coords, newcoords, c); 
    // empties old cells, draws new ones 
    return true; // means the move was successful 
}

/* Grid::checkEmpty(int x, int y, vector coords)
 * Used to determine if the current cell at x, y is occupied by a 
 * member of the coords (used to prevent repetitive code)
 */
bool Grid::checkEmpty(int x, int y, vector <pair<int, int>> coords) {
    int flag = true;
    for (int k = 0; k < 4; ++k) {
        if (x == coords.at(k).first && y == coords.at(k).second) { 
            flag = false; // if the block currently belongs to a 
            // another cell of the block in its 
            // unmoved position this is okay,
            //  and hence flag is cleared. 
            break;
        } 
    }
    return flag;
}

/* Grid::validate(int x, int y)
 * Used by other functions in Grid to ensure x and y 
 * values are within the Grids bounds. 
 * x = col, y = row. 
 * Note: return value of 0 = invalid, 1 = valid.  
 */
bool Grid::validate(int x, int y)  {
     // ensures x(col) is within bounds 
    if (x > 10 || x < 0) { 
        return false;
     // ensures y (row) is within bunds 
    } else if (y > 17 || y < 0) { 
        return false;
    } 
    return true; // coordinates valid 
}

/* Grid::changeBlock(State p, Block *b)
 * Used when the I/J/S/L/O/T/Z commands are called. 
 * Effects: will print output if conversion is invalid. 
 */
void Grid::changeBlock(State p, shared_ptr<Block> b) {
    int x = b->getBottomX() - this->p->getBlock()->getBottomX();
    int y = b->getBottomY() - this->p->getBlock()->getBottomY();
    // obtains the change in x and y from the start positions
    vector <pair<int, int>> oldc = this->p->getBlock()->getCoords();
    vector <pair<int, int>> coords = b->getCoords();
    for (int i = 0; i < 4; ++i) {
        coords.at(i).first -= x;
        coords.at(i).second -=y; 
        // checks to make sure the coordinates are valid 
        // using Grid::validate 
        if (!validate(coords.at(i).first, coords.at(i).second)) {
            // if it is not possible, return 
            cout << "Unable to change block" << endl;
            return; // will not make change happen 
        }
    }
    for (int i = 0; i < 4; ++i) {
        int x1 = coords.at(i).first;
        int y1 = coords.at(i).second;
        // if desired cell is not empty, will see if it is 
        // currently occupied by the current block 
        if (!this->theGrid.at(y1).at(x1).isEmpty()) {
            bool flag = checkEmpty(x1, y1, oldc);
            if (flag == 1) { // will return if not possible.
                return;
            }
        }
    }
    b->setCoords(coords); // will set the blocks to permanently 
    // be in their new updated position 
    // (each cell updated by -x, -y).
    char c = b->getType();
    reprint(p, oldc, coords, c);
    if (this->p->getLevel() != 6) {
        // will not output in level 6 because of hide mode. 
        cout << *this;
    }
    this->p->setBlock(b); 
    // ensures the next block is correctly updated! 
}

/* Grid::down(State p)
 * Will move down by 1. Has 3 return numbers! 
 * 0 = unable to move down 
 * -1 = moved down, but will not be able to move down again 
 * 1 = moved down, and can move down again! 
 */
int Grid::down(State p) {
    shared_ptr<Block> b = this->getPlayer()->getBlock();
    vector <pair<int, int>> coords = b->getCoords();
    b->move(DOWN);
    vector <pair<int, int>> newcoords = b->getCoords();
    for (int i = 0; i < 4; ++i) {
        int x = newcoords.at(i).first;
        int y = newcoords.at(i).second;
        if (!validate(x, y)) {
            b->setCoords(coords);
            return false;
        } 
        if (!this->theGrid.at(y).at(x).isEmpty()) { 
            bool flag = checkEmpty(x, y, coords);
            if (flag == 1) { 
                b->setCoords(coords);
                return false;
            }
        }
    } 
    char c = b->getType();
    reprint(p, coords, newcoords, c);
    for (int i = 0; i < 4; ++i) {
        int x = newcoords.at(i).first;
        int y = newcoords.at(i).second;
        if (y == 0) {
            return -1;
        } else if (!this->theGrid.at(y - 1).at(x).isEmpty()) {
            bool flag = checkEmpty(x, y - 1, newcoords);
            if (flag == true) {
                // this means that the block is unable to be moved 
                // further down 
                return -1;
            }
        }
    }
    return 1;
}

/* Grid::drop(State p) 
 * Iterates on down, to go down as much as possible, will call 
 * rowClear as well, and if there has been 5 rows without clearing 
 * a block, it will call the brown function to drop a block if 
 * the players level is >= 4. 
 */
bool Grid::drop(State p) {
    int val = 1;
    while (val == 1) {
        val = this->down(p);
    }
    ++this->counter; // increments the counter 
    const int row = rowclear(p);
    if ((this->counter != 0) && (this->counter % 5 == 0) && 
    (this->p->getLevel() >= 4)) {
        // if the counter is not zero, the counter is divisible 
        // by 5 and the level is 4 or greater
        // we need to drop a brown block 
        this->brown(p, this->p->getLevel());
    }

    return (row >= 2);
}

/* Grid::brown(State p, int n)
 * Used in levels 4-6. In level 4, will drop one 
 * brown block in the first available position in col 5. 
 * In levels 5 and 6, will drop one on every column. 
 */
void Grid::brown(State p, int n) { 
    if (this->p->getLevel() < 4) { 
        return;
    }
    if (n == 4) { 
        bool flag = true;
        for (int i = 14; i >= 0; --i) {
            if (this->theGrid.at(i).at(5).isEmpty()) {
                flag = false;
                if (i == 0) {  // will not check row below as with 
                // next loop because will throw 
                // std::out_of_range exception 
                    this->theGrid.at(i).at(5).setType('*');
                    this->td->notify(p, i, 5, '*');
                    if (!this->text && this->gr) { // to see if 
                    // text mode is activated 
                        this->gr->notify(p, i, 5, '*');
                    }
                    break;
                } else if (!this->theGrid.at(i-1).at(5).isEmpty()) {
                    this->theGrid.at(i).at(5).setType('*');
                    this->td->notify(p, i, 5, '*');
                    if (!this->text && this->gr) { 
                        // to see if text mode is activated 
                        this->gr->notify(p, i, 5, '*');
                    }
                    break;
                }
            }
        }
        if (flag == true) {
            throw GameOver{p}; // if it impossiible to set 
            // the brown block, the game is over. .
        }
    } else { // same loop as above, however
    //  drops a block on EVERY column. 
        for (int k = 0; k < 11; ++k) {
            bool flag = true;
            for (int i = 14; i >= 0; --i) {
                if (this->theGrid.at(i).at(k).isEmpty()) {
                    flag = false;
                    if (i == 0) { // special cause for 0, because of 
                    // std::out_of_range exception. 
                        this->theGrid.at(i).at(k).setType('*');
                        this->td->notify(p, i, k, '*');
                        if (!this->text && this->gr) {
                             // to see if text mode is activated 
                            this->gr->notify(p, i, k, '*');
                        }
                        break;
                    } else if (!this->theGrid.at(i-1).at(k).isEmpty()) {
                        this->theGrid.at(i).at(k).setType('*');
                        this->td->notify(p, i, k, '*');
                        if (!this->text && this->gr) { 
                            // to see if text mode is activated 
                         this->gr->notify(p, i, k, '*');
                        }
                        break;
                    }
                }
            }
            if (flag == true) { 
                // will throw GameOver if it is unable to 
            // drop a block in a row
                    throw GameOver{p};
            }
        }
    }
}

/* Grid::fixBlind(State p) 
 * The graphics of the game will be completely set to black. 
 * If this happens, fixBlind will reupdate the entire graphics
 * for the current player. 
 */
void Grid::fixBlind(State p) {
    if (text) { // if the program is in text mode, 
    // there is no need to update graphics. 
        return;
    }
    for (int row = 0; row < 18; ++row) {
        for  (int col = 0; col < 11; ++col) {
            // calls one each cell (198 total)
            this->gr->blindnotify(p, row, col, 
            this->theGrid.at(row).at(col).getType());
        }
    }
}


/* Grid::rotate(State p)
 * Will rotate the blocks in a CW direction. This will update
 * graphics and textdisplay automatically if a change occurs. 
 */
void Grid::rotate(State p) {
    shared_ptr<Block> b = this->p->getBlock();
    vector <pair<int, int>> coords = b->getCoords();
    b->setCoords(b->rotate()); // sets coords through rotate 
    vector <pair<int, int>> newCoords = b->getCoords();
    for (int i = 0; i < 4; ++i) {
        int x = newCoords.at(i).first;
        int y = newCoords.at(i).second;
        if (!validate(x, y)) {
            // validate the coordinates through Grid::validate
            b->setCoords(coords);
            return;
        }
        if (!this->theGrid.at(y).at(x).isEmpty()) { 
            int flag = checkEmpty(x, y, coords);
            if (flag == 1) { 
                b->setCoords(coords);
                return;
            }
        }
    }
    b->switchOrientation(); // from h to v or v to h 
    // for block's rotate
    char c = b->getType();
    reprint(p, coords, newCoords, c); // redraws cells 
}

/* Grid::reprint(State p, vector coords, 
*  vector newCoords, char c)
 * Used to "erase" all the cells from the vector coords, 
 * and drawall the cells from vector newCoords with type c.
 */
void Grid::reprint(State p, vector <pair<int, int>> coords, 
vector <pair<int, int>> newCoords, char c) { 
    for (int i = 0; i < 4; ++i) {
        int oldx = coords.at(i).first;
        int oldy = coords.at(i).second;
        this->clear(p, oldy, oldx); 
        // empties all prior cells to ' ' (empty)
    }
    for (int k = 0; k < 4; ++k) {
        int x = newCoords.at(k).first;
        int y = newCoords.at(k).second;
        this->theGrid.at(y).at(x).setType(c);
        this->td->notify(p, y, x, c);
        if (!this->text && this->gr) { // only updates graphics
        // if not in text mode 
                this->gr->notify(p, y, x, c);
        }
    } 
}

/* Grid::clear(State p, int row, int col)
 * Used to "erase" a cell and revert to type 
 * empty (' ').
 */
void Grid::clear(State p, int row, int col) {
    char c = ' ';
    this->theGrid.at(row).at(col).setType(c);
    this->td->notify(p, row, col, c);
    if (!this->text && this->gr) {
        // only updates graphics if not in text mode 
        this->gr->notify(p, row, col, c);
    }
}

/* Grid::isRowFull(int n)
 * Will return whether or not a particlar row is full. 
 * Used in the Grid::rowClear() function. 
 */
bool Grid::isRowFull(int n) { 
    for (int i = 0; i < 11; ++i) {
         if (this->theGrid.at(n).at(i).isEmpty() == true) {
             // if a cell is empty, it clearly is not full
             // the type of what it is when not empty does 
             // not matter, 
            return false;
        }
    } 
    return true;
}     

/* Grid::score(int n, int level)
 * Will increment the players score by 
 * (n + level)^2. 
 */
void Grid::score(int n, int level) { 
    if (n == 0) { // useless to update 
    // can incorrectly cause a wrong value 
    // if level > 0. 
        return;
    }
    int score = n + level;
    score *= score;
    this->getPlayer()->addScore(score);
    if (!this->text && this->gr) {
        // will only update the graphics 
        // if not in text mode 
        this->gr->notifyScore();
    }
}

/* Grid::rowClear(state p)
 * will clear a row, and call the score function to change
 * the score. 
 */
int Grid::rowclear(State p) {
    int level = this->getPlayer()->getLevel(); // level of player
    int n = 0; // # of rows cleared
    for (int i = 0; i < 18; ++i) {
        if (isRowFull(i)) { 
            ++n;
            for (int k = i; k < 16; ++k) {
                for (int j = 0; j < 11; ++j) {
                    char c = this->theGrid.at(k+1).at(j).getType();
                    this->theGrid.at(k).at(j).setType(c); 
                    this->td->notify(p, k, j, c);
                    if (!this->text && this->gr) {
                        this->gr->notify(p, k, j, c);
                     }
                }
            }
            for (int m = 0; m < 11; ++m) {
                clear(p, 17, m);
            }
            i = -1;
            // if a row is cleared, restart the entire loop
            // -1 will become 0 on the next iteration. 
        }
    }
    if (n > 0) {
        // means a drop occured, and resets the counter 
        this->counter = 0;
    }
    score(n, level);
    return n; // used by the drop function 
    // to determine if a specialAction should occur or not. 
}

/* Grid::setTD(TextDisplay *td)
 * Used to increment a new TD when initalized 
 */
void Grid::setTD(shared_ptr<TextDisplay> td) { 
    this->td = td;
}

/* Grid::setGraphics(Graphics *gr)
 * Used to set a Graphics pointer. If the program 
 * is in "-text" mode, will be a nullptr.  
 */
void Grid::setGraphics(shared_ptr<Graphics> gr) { 
    this->gr = gr;
}


/* Grid::getPlayer() 
 * Will return the current player. 
 * Mostly used by Controller, to not have to check which 
 * players turn it in (use getGrid()->getPlayer()).
 */              
shared_ptr<Player> Grid::getPlayer() {
    return this->p;
}

/* operator overload << for a grid. 
 * Will make reference to the TextDisplay output.
 * Refer to textdisplay.cc 
 */
ostream &operator<<(ostream &out, const Grid &gr) { 
    out << *gr.td;
    return out;
}

