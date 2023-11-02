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
    Board(int initialWidth,int initialHeigth);
    Sprite* Init(Engine* engine);

    Piece pieces[10][20];

    int width, heigth;
};

#endif 
