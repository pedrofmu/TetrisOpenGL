#include "include/movingPiece.h"
#include "include/game.h"
#include "include/piece.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>
#include <utility>
#include "include/piece.h"


const int IStruct[4][4] =
   {  
      {0,0,0,0},
      {0,0,0,0},
      {1,1,1,1},
      {0,0,0,0}
   }; 

const int OStruct[2][2] =
   {  
      {1,1},
      {1,1},
   }; 

const int TStruct[3][3] =
   {  
      {0,0,1},
      {0,1,1},
      {0,0,1}
   }; 

const int LStruct[3][3] =
   {  
      {0,0,0},
      {0,0,1},
      {1,1,1},
   }; 

const int ZStruct[3][3] =
   {  
      {0,0,0},
      {0,1,1},
      {1,1,0},
   }; 

bool canRotate = true;

MovingPiece::MovingPiece(){
   std::random_device rd;
   std::mt19937 gen(rd());

   std::uniform_int_distribution<int> structRandom(0, 4);  

   int structToUse = structRandom(gen);

   switch (structToUse) {
     case 0:
        currentStruct.resize(4, std::vector<int>(4, 0));
        for (int i = 0; i < 4; i++){
           for (int j = 0; j < 4; j++){
              currentStruct[i][j] = IStruct[i][j];
           }
        }
     break;
     case 1:
        currentStruct.resize(2, std::vector<int>(2, 0));
        for (int i = 0; i < 2; i++){
           for (int j = 0; j < 2; j++){
              currentStruct[i][j] = OStruct[i][j];
           }
        }
     break;
     case 2:
        currentStruct.resize(3, std::vector<int>(3, 0));
        for (int i = 0; i < 3; i++){
           for (int j = 0; j < 3; j++){
              currentStruct[i][j] = TStruct[i][j];
           }
        }
     break;
     case 3:
        currentStruct.resize(3, std::vector<int>(3, 0));
        for (int i = 0; i < 3; i++){
           for (int j = 0; j < 3; j++){
              currentStruct[i][j] = LStruct[i][j];
           }
        }
     break;
     case 4:
        currentStruct.resize(3, std::vector<int>(3, 0));
        for (int i = 0; i < 3; i++){
           for (int j = 0; j < 3; j++){
              currentStruct[i][j] = ZStruct[i][j];
           }
        }
     break;
   }

   currentX = 5 - (currentStruct.size()/2);
   currentY = -1;

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

void MovingPiece::rotateLeft(Piece currentBoard[10][20]){
   if (!canRotate)
      return;

   float magicNumber = (currentStruct.size() - 1.0f) / 2.0f;
   std::vector<std::pair<float, float>> currentPositions;
   for (int i = 0; i < currentStruct.size(); ++i) {
       for (int j = 0; j < currentStruct.size(); ++j) {
         if (currentStruct[i][j]){
            currentPositions.push_back(std::make_pair(i - magicNumber, (j - magicNumber)));
         }
       }
   }

   std::vector<std::pair<float, float>> newPositions;
   for (int i = 0; i < currentPositions.size(); ++i){
      float x = currentPositions[i].first * std::cos(3.14159 / 2) - currentPositions[i].second * std::sin(3.14159 / 2);
      float y = currentPositions[i].first * std::sin(3.14159 / 2) + currentPositions[i].second * std::cos(3.14159 / 2);
      newPositions.push_back(std::make_pair(x, y)); 
   }

   //Comprobar que se pude rotar   std::round(newPositions[i].first + magicNumber)   std::round(newPositions[i].second + magicNumber)
   for (int i = 0; i < newPositions.size(); ++i){
      if(currentBoard[int(currentX + std::round(newPositions[i].first + magicNumber))][int(currentY + std::round(newPositions[i].second + magicNumber))].color != empty){
         return;
      } 
      if (currentX + std::round(newPositions[i].first + magicNumber) > 9  || currentX  < 0){
         std::cout << "a" << std::endl;
         return;
      }
   }

   for (int i = 0; i < currentStruct.size(); ++i) {
       for (int j = 0; j < currentStruct.size(); ++j) {
         currentStruct[i][j] = 0;
       }
   } 

   for (int i = 0; i < newPositions.size(); ++i){
      currentStruct[int (std::round(newPositions[i].first + magicNumber))][int (std::round(newPositions[i].second + magicNumber))] = 1; 
   }

   canRotate = false;
   auto stablishCanRotate = [](){
      std::this_thread::sleep_for(std::chrono::milliseconds(300));

      canRotate = true;
   };
   std::thread tarea(stablishCanRotate);
   tarea.detach();
}
