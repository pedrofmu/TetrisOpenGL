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
   std::random_device rd;
   std::mt19937 gen(rd());

   std::uniform_int_distribution<int> structRandom(0, 4);  

   int structToUse = structRandom(gen);

   switch(structToUse){
      case 0:
      for (int i = 0; i < 3; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = IStruct[i][j];
         }
      }
      break;
      case 1:
      for (int i = 0; i < 3; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = OStruct[i][j];
         }
      }
      break;
      case 2:
      for (int i = 0; i < 3; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = TStruct[i][j];
         }
      }
      break;
      case 3:
      for (int i = 0; i < 3; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = LStruct[i][j];
         }
      }
      break;
      case 4:
      for (int i = 0; i < 3; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = ZStruct[i][j];
         }
      }
      break;
   }
   

   currentX = 4;
   currentY = 0;

   std::uniform_int_distribution<int> colorRandom(1, 1);  

   int theColor = colorRandom(gen);

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
