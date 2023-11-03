#include "include/board.h"
#include "include/engine.h"
#include "include/piece.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>

Board::Board(){
   for (int i = 0; i < 10; i++)
   {
      for (int j = 0; j < 20; j++)
      {
         int piece = (2*(sin((3.14159 * j * i) / 2))) + 2;
         switch (piece)
         {
            case red:
            pieces[i][j] = Piece(red, empty);
            break;
            case magenta:
            pieces[i][j] = Piece(magenta, empty);
            break;
            case yellow:
            pieces[i][j] = Piece(yellow, empty);
            break;
            case cyan:
            pieces[i][j] = Piece(cyan, empty);
            break;
            case null:
            pieces[i][j] = Piece(null, empty);
            break;
         }
      }
   }
}


