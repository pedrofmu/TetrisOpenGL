#include "include/engine.h"
#include "include/game.h"
#include "include/glm/ext/vector_float2.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <thread>

//Crear el juego
Game::Game(Engine* engine){
   prueba = engine->addSprite("../assets/textures/coche.jpg", 400, 500, 200, 200);

   _engine = engine;

   engine->addUpdateCallBack(this);
   engine->addInputCallBack(this);
};

//funcion update, gracias al estar en el call back se ejecuta cada "tick" del juego
void Game::update(){
   if ((glfwGetTime() - lastTime) >= timeToPass) {
      //Coloca aquí tu código
      glm::vec2 position = prueba->getPosition();

      int key = keyToProcess;
      switch (key) {
         case GLFW_KEY_A:
            prueba->setPosition(position.x - 10, position.y);
         break;
         case GLFW_KEY_D:
            prueba->setPosition(position.x + 10, position.y);
         break;
      }
      lastTime = glfwGetTime();
      keyToProcess = 0;
   }
};

void Game::processInput(int key){
   keyToProcess = key;
};
