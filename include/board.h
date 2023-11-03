#ifndef BOARD
#define BOARD
#include "include/engine.h"
#include "include/rendering/sprite.h"
#include "include/piece.h"

#include "iostream"
#include <vector>

//Clase para representar el tablero
class Board{
public:
    Board();

    Piece pieces[10][20];
};

#endif 
