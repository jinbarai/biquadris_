#ifndef STATE_H
#define STATE_H

enum class State { p1 , p2 };

class InvalidMove{}; // for exceptions

struct GameOver{
    public:
    State player;
}; 

#endif
