#include "include/movingPiece.h"
#include "include/game.h"
#include "include/piece.h"
#include <cmath>
#include <iostream>
#include <random>
#include <utility>

const int IStruct[4][4] =
   {  
      {0,0,0,0},
      {0,0,0,0},
      {1,1,1,1},
      {0,0,0,0}
   }; 

const int OStruct[4][4] =
   {  
      {0,0,0,0},
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0}
   }; 

const int TStruct[4][4] =
   {  
      {0,0,0,0},
      {0,0,0,1},
      {0,0,1,1},
      {0,0,0,1}
   }; 

const int LStruct[4][4] =
   {  
      {0,0,0,0},
      {0,0,0,1},
      {0,1,1,1},
      {0,0,0,0}
   }; 

const int ZStruct[4][4] =
   {  
      {0,0,0,0},
      {0,0,1,1},
      {0,1,1,0},
      {0,0,0,0}
   }; 

MovingPiece::MovingPiece(){
   std::random_device rd;
   std::mt19937 gen(rd());

   std::uniform_int_distribution<int> structRandom(0, 4);  

   int structToUse = structRandom(gen);

   switch(structToUse){
      case 0:
      for (int i = 0; i < 4; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = IStruct[i][j];
         }
      }
      break;
      case 1:
      for (int i = 0; i < 4; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = OStruct[i][j];
         }
      }
      break;
      case 2:
      for (int i = 0; i < 4; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = TStruct[i][j];
         }
      }
      break;
      case 3:
      for (int i = 0; i < 4; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = LStruct[i][j];
         }
      }
      break;
      case 4:
      for (int i = 0; i < 4; i++){
         for (int j = 0; j < 4; j++){
            currentStruct[i][j] = ZStruct[i][j];
         }
      }
      break;
   }
   

   currentX = 4;
   currentY = 0;

   std::uniform_int_distribution<int> colorRandom(1, 4);  

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

void MovingPiece::rotateLeft(){
   std::vector<std::pair<float, float>> currentPositions;
   for (int i = 0; i < 4; ++i) {
       for (int j = 0; j < 4; ++j) {
         if (currentStruct[i][j]){
            currentPositions.push_back(std::make_pair(i - 1.5, (j - 1.5)));
         }
       }
   }

   std::vector<std::pair<float, float>> newPositions;
   for (int i = 0; i < currentPositions.size(); ++i){
      float x = currentPositions[i].first * std::cos(3.14159 / 2) - currentPositions[i].second * std::sin(3.14159 / 2);
      float y = currentPositions[i].first * std::sin(3.14159 / 2) + currentPositions[i].second * std::cos(3.14159 / 2);
      newPositions.push_back(std::make_pair(x, y)); 
   }

   for (int i = 0; i < 4; ++i) {
       for (int j = 0; j < 4; ++j) {
         currentStruct[i][j] = 0;
       }
   } 

   for (int i = 0; i < newPositions.size(); ++i){
      currentStruct[int (std::round(newPositions[i].first + 1.5))][int (std::round(newPositions[i].second + 1.5))] = 1; 
   }
}
