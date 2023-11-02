#include "include/engine.h"
#include "include/game.h"
#include "include/glm/ext/vector_float2.hpp"
#include "include/board.h"
#include "include/rendering/stb_image.h"
#include "include/rendering/tileSprite.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <ostream>
#include <thread>

//Crear el juego
Game::Game(Engine* engine){
   Board board(300, 600);

   _engine = engine;

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

   _engine->pauseEngine();
   for (int i = 0; i < 10; i++){
      for (int j = 0; j < 20; j++){
         tiles[i][j] = new TileSprite(texutres[0], 250 + (i * 40), 780  - (j * 40), 40, 40);
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
         _engine->addSprite(tiles[i][j]);
      }
   }
   _engine->resumeEngine();
};

//funcion update, gracias al estar en el call back se ejecuta cada "tick" del juego
void Game::update(){
   if ((glfwGetTime() - lastTime) >= timeToPass) {
      //Coloca aquí tu código
      int key = keyToProcess;
      switch (key) {
         case GLFW_KEY_A:
         break;
         case GLFW_KEY_D:
         break;
      }
      lastTime = glfwGetTime();
      keyToProcess = 0;
   }
};

void Game::processInput(int key){
   keyToProcess = key;
};
