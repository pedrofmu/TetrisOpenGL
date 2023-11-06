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
         pieces[i][j] = Piece(empty);
      }
   }
}


