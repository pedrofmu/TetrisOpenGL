#ifndef MOVINGPIECE
#define MOVINGPIECE

#include "include/board.h"
#include "include/piece.h"

class MovingPiece{
public:
    MovingPiece();

    int currentX, currentY;

    int currentStruct[3][4];

    COLOR color;
};

#endif
