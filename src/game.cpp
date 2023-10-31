#include "include/engine.h"
#include "include/game.h"
#include "include/glm/ext/vector_float2.hpp"
#include <cstdio>
#include <iostream>

//Crear el juego
Game::Game(Engine* engine){
   prueba = engine->addSprite("../assets/textures/coche.jpg", 0,0, 200, 200);

   _engine = engine;

   engine->addUpdateCallBack(this);
   engine->addInputCallBack(this);
};

void Game::update(){
};

void Game::processInput(int key){
   glm::vec2 position = prueba->getPosition();
   switch (key) {
      case GLFW_KEY_W:
         prueba->setPosition(position.x, position.y + 10);
         break;
      case GLFW_KEY_A:
         prueba->setPosition(position.x - 10, position.y);
         break;
      case GLFW_KEY_D:
         prueba->setPosition(position.x + 10, position.y);
         break;
      case GLFW_KEY_S:
         prueba->setPosition(position.x, position.y - 10);
         break;
   }
};
