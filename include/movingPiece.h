#ifndef MOVINGPIECE
#define MOVINGPIECE

#include "include/board.h"
#include "include/piece.h"

#include <iostream>

class MovingPiece{
public:
    MovingPiece();

    int currentX, currentY;

    std::vector<std::vector<int>> currentStruct;

    COLOR color;

    void rotateLeft(Piece currentBoard[10][20]);
};

#endif
