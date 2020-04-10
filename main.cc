#include "cell.h"
#include "levels.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "grid.h"
#include "textdisplay.h"
#include "block.h"
#include "iblock.h"
#include "controller.h"
#include "player.h"
#include <string>
using namespace std;

int main() { 
    Player *p1 = new Player{0, "he", 0};
    Player *p2 = new Player{0, "hi", 0};
    Grid gr;
    gr.init(p1, p2);
    return 0;
}
