#include "include/movingPiece.h"
#include "include/piece.h"

const int defaulStruct1[3][4] =
   {  {0,0,0,1},
      {0,1,1,1},
      {0,0,0,1}
   }; 

MovingPiece::MovingPiece(){
   for (int i = 0; i < 3; i++){
      for (int j = 0; j < 4; j++){
         currentStruct[i][j] = defaulStruct1[i][j];
      }
   }

   currentX = 4;
   currentY = 0;

   color = red;
}
