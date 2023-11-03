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
    Piece(COLOR initialColor, STATE initialState): color(initialColor), state(initialState){};

    COLOR color;
    STATE state;
};
#endif 
