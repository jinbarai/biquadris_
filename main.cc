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
    levels *l = new levelzero();
    Player *p1 = new Player{0, "he", l, 0};
    levels *l2 = new levelzero();
    Player *p2 = new Player{0, "hi", l2, 0};
    Grid gr;
    gr.init(p1, p2);
    return 0;
}
