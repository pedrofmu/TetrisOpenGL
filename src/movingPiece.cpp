#include "include/movingPiece.h"
#include "include/piece.h"
#include <iostream>
#include <random>

const int IStruct[3][4] =
   {  {0,0,0,0},
      {1,1,1,1},
      {0,0,0,0}
   }; 

const int OStruct[3][4] =
   {  {0,0,0,0},
      {0,0,1,1},
      {0,0,1,1}
   }; 

const int TStruct[3][4] =
   {  {0,0,0,1},
      {0,0,1,1},
      {0,0,0,1}
   }; 

const int LStruct[3][4] =
   {  {0,0,0,0},
      {0,0,0,1},
      {0,1,1,1}
   }; 

const int ZStruct[3][4] =
   {  {0,0,0,0},
      {0,0,1,1},
      {0,1,1,0}
   }; 

MovingPiece::MovingPiece(){
   for (int i = 0; i < 3; i++){
      for (int j = 0; j < 4; j++){
         currentStruct[i][j] = LStruct[i][j];
      }
   }

   currentX = 4;
   currentY = 0;

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<int> distribution(1, 4);  


   int theColor = distribution(gen);

   switch (theColor){
      case red:
         color = red;
      break;
      case magenta:
         color = magenta;
      break;
      case yellow:
         color = yellow;
      break;
      case cyan:
         color = cyan;
      break;
   }
}
