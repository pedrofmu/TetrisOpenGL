#ifndef PIECE
#define PIECE

enum COLOR{
    red,
    magenta,
    yellow,
    cyan,
    null 
};

enum STATE{
    empty,
    moving,
    stop
};

class Piece{
public:
    Piece(): color(null), state(empty){};

    COLOR color;
    STATE state;
};
#endif 
