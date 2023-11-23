#include "include/engine.h"
#include "include/game.h"
#include "include/glm/ext/vector_float2.hpp"
#include "include/board.h"
#include "include/piece.h"
#include "include/rendering/stb_image.h"
#include "include/rendering/tileSprite.h"
#include "include/board.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <ostream>
#include <thread>
#include <vector>
#include "include/movingPiece.h"

//Crear el juego
Game::Game(Engine* mainEngine){
   //Inicializa las variables necesarias
   engine = mainEngine;
   board = Board();
   staticPieces = std::vector<StaticPiece>();

   engine->addUpdateCallBack(this);
   engine->addInputCallBack(this);

   //Crea las texturas
   std::string pathToTextures[]{
      "../assets/textures/emptyTile.png", 
      "../assets/textures/redTile.png", 
      "../assets/textures/magentaTile.png", 
      "../assets/textures/yellowTile.png",
      "../assets/textures/cyanTile.png"
   };

   //Crea las texturas
   for (int i = 0; i < 5; i++)
   {
      texutres[i] = engine->createRGBATexture(pathToTextures[i]);
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
   }

   //Inizializa el tablero
   for (int i = 0; i < 10; i++){
      for (int j = 0; j < 20; j++){
         tiles[i][j] = new TileSprite(texutres[board.pieces[i][j].color], 250 + (i * 40), 780  - (j * 40), 40, 40);
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
         engine->addSprite(tiles[i][j]);
      }
   }

   movingPiece = new MovingPiece();
};

//funcion update, gracias al estar en el call back se ejecuta cada "tick" del juego
void Game::update(){
   //limpa las pieces
   for (int i = 0; i < 10; i++){
      for (int j = 0; j < 20; j++){
         board.pieces[i][j].color = empty;
      }
   }
   
   //Dibujar las piezas estaticas
   for(int i = 0; i < staticPieces.size(); i++){
      board.pieces[staticPieces[i].x][staticPieces[i].y].color = staticPieces[i].color;
   }
   
   //procesa el input
   switch (keyToProcess) {
      case GLFW_KEY_A:
         if (isValidMove(movingPiece->currentX - 1, movingPiece->currentY, movingPiece->currentStruct))
            movingPiece->moveLeft();
      break;
      case GLFW_KEY_SPACE:
         movingPiece->rotateLeft(board.pieces);
      break;
      case GLFW_KEY_D:
         if (isValidMove(movingPiece->currentX + 1, movingPiece->currentY, movingPiece->currentStruct))
            movingPiece->moveRigth();
      break;
   }
   keyToProcess = 0;

   //El bucle de movimiento
   if ((glfwGetTime() - lastTime) >= timeToPass) {
      movePiece();

      lastTime = glfwGetTime();
   }

   //Establecer las casillas de la pieza
   for (int i = 0; i < movingPiece->currentStruct.size(); i++){
      for (int j = 0; j < movingPiece->currentStruct[i].size(); j++){
         if (movingPiece->currentStruct[i][j] == 1){
            board.pieces[movingPiece->currentX + i][movingPiece->currentY + j].color = movingPiece->color;
         }
      }
   }
      
   //Actualiza las texutras
   for (int i = 0; i < 10; i++){
      for (int j = 0; j < 20; j++){
         tiles[i][j]->setTexutre(texutres[board.pieces[i][j].color]); 
      }
   }
};

//Guarda el input
void Game::processInput(int key){
   keyToProcess = key;
};

//Mueve la pieza hacia abajo
void Game::movePiece(){
   //Baja la pieza una casilla
   movingPiece->currentY++;
   
   //Comprobar si hay que hacer estatica la pieza
   if (movingPiece->currentY + movingPiece->currentStruct.size() >= 20){
      placePiece();
      return;
   }else{
      for (int j = 0; j < movingPiece->currentStruct.size(); j++){
        for (int i = 0; i < movingPiece->currentStruct.size(); i++){
           if (board.pieces[movingPiece->currentX + i][movingPiece->currentY + j + 1].color != empty && movingPiece->currentStruct[i][j] == 1){
              placePiece();
              return;
           }
        }
      }
      
   }
}

//Poner una pieza en su lugar
void Game::placePiece(){
   //Detectar si has perdido
   if (movingPiece->currentY <= movingPiece->currentStruct.size()){
      gameOver();
      return;
   }

   //Añadir piezas estaticas
   for (int i = 0; i < movingPiece->currentStruct.size(); i++){
      for (int j = 0; j < movingPiece->currentStruct[i].size(); j++){
         if (movingPiece->currentStruct[i][j] == 1){
            staticPieces.push_back(StaticPiece(movingPiece->currentX + i,movingPiece->currentY + j, movingPiece->color));
         }
      }
   }

   //Dibuja las piezas estaticas
   for(int i = 0; i < staticPieces.size(); i++){
      board.pieces[staticPieces[i].x][staticPieces[i].y].color = staticPieces[i].color;
   }

   //Comprobar eliminar piezas 
   for (int j = 0; j < 20; j++){
      bool hasToDelete = true;
      for(int i = 1; i < 10; i++){
         if (board.pieces[i][j].color == empty){
            hasToDelete = false;
            break;
         }
      }

      if (hasToDelete)
         deleteRow(j);
   }

   delete movingPiece;
   movingPiece = new MovingPiece();
}

//Delete a row
void Game::deleteRow(int column){
   std::vector<int> elementsToRemove = std::vector<int>();
   for (int i = 0; i < 10; i++){
      for(int a = 0; a < staticPieces.size(); a++){
         if (staticPieces[a].x == i && staticPieces[a].y == column){
            staticPieces.erase(staticPieces.begin() + a);
         }
      }
   }

   for(int a = 0; a < staticPieces.size(); a++){
      if (staticPieces[a].y <= column)
         staticPieces[a].y++;
   }
}

bool Game::isValidMove(int newX, int newY, std::vector<std::vector<int>>& structure){
   for(int i = 0; i < structure.size(); i++){
      for (int j = 0; j < structure.size(); j++){
         if (structure[i][j] == 1){
            if (newX + i > 9 || newX + i < 0){
               return false;
            }

            if (board.pieces[newX + i][newY + j].color != empty){
               return false;
            }
         }
      }
   }
   
   return true;
}

void Game::gameOver(){
   engine->pauseEngine();

   //Dibujar las piezas estaticas
   staticPieces.clear(); 

   //limpa las pieces
   for (int i = 0; i < 10; i++){
      for (int j = 0; j < 20; j++){
         board.pieces[i][j].color = empty;
      }
   }

   delete movingPiece;
   movingPiece = new MovingPiece();

   engine->resumeEngine();
}
