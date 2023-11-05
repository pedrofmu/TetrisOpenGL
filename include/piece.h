#ifndef PIECE
#define PIECE

enum COLOR{
    null, 
    red,
    magenta,
    yellow,
    cyan,
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
