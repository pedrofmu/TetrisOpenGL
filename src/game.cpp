#include "include/engine.h"
#include "include/game.h"
#include "include/glm/ext/vector_float2.hpp"
#include "include/board.h"
#include "include/rendering/stb_image.h"
#include "include/rendering/tileSprite.h"
#include "include/board.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <ostream>
#include <thread>
#include "include/movingPiece.h"

//Crear el juego
Game::Game(Engine* engine){
   _engine = engine;
   board = Board();

   _engine->addUpdateCallBack(this);
   _engine->addInputCallBack(this);

   std::string pathToTextures[]{
      "../assets/textures/emptyTile.png", 
      "../assets/textures/redTile.png", 
      "../assets/textures/magentaTile.png", 
      "../assets/textures/yellowTile.png",
      "../assets/textures/cyanTile.png"
   };

   for (int i = 0; i < 5; i++)
   {
      texutres[i] = _engine->createTexture(pathToTextures[i]);
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
   }

   for (int i = 0; i < 10; i++){
      for (int j = 0; j < 20; j++){
         tiles[i][j] = new TileSprite(texutres[board.pieces[i][j].color], 250 + (i * 40), 780  - (j * 40), 40, 40);
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
         _engine->addSprite(tiles[i][j]);
      }
   }

   movingPiece = new MovingPiece();
};

//funcion update, gracias al estar en el call back se ejecuta cada "tick" del juego
void Game::update(){
   if ((glfwGetTime() - lastTime) >= timeToPass) {
      int key = keyToProcess;
      switch (key) {
         case GLFW_KEY_A:
            movingPiece->currentX--;
         break;
         case GLFW_KEY_D:
            movingPiece->currentX++;
         break;
      }

      movingPiece->currentY++;

      for (int i = movingPiece->currentX - 1; i <= movingPiece->currentX + 1; i++){
         for (int j = movingPiece->currentY - 4; j <= movingPiece->currentY - 1; j++){
            if (movingPiece->currentStruct[i - (movingPiece->currentX - 1)][j - (movingPiece->currentY - 4)] == 1)
               board.pieces[i][j].color = movingPiece->color;
            else 
               board.pieces[i][j].color  = null;
         }
      }

      for (int i = 0; i < 10; i++){
         for (int j = 0; j < 20; j++){
            tiles[i][j]->setTexutre(texutres[board.pieces[i][j].color]); 
         }
      }

      lastTime = glfwGetTime();
      keyToProcess = 0;
   }
};

void Game::processInput(int key){
   keyToProcess = key;
};
