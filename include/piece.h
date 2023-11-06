#ifndef PIECE
#define PIECE

enum COLOR{
    empty, 
    red,
    magenta,
    yellow,
    cyan,
};

class Piece{
public:
    Piece(): color(empty){};
    Piece(COLOR initialColor): color(initialColor){};

    COLOR color;
};
#endif 
