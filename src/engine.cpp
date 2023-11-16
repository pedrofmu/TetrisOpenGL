#include "include/engine.h"
#include "include/glm/fwd.hpp"
#include "include/rendering/sprite.h"
#include "include/rendering/stb_image.h"
#include <algorithm>
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <ostream>
#include <string>
#include <vector>
#include <chrono>
#include <include/glm/glm.hpp>
#include <include/glm/gtc/matrix_transform.hpp>

int w_width;
int w_heigth;
//Cambia el viewport segun se redimensione la pantalla
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   w_width = width;
   w_heigth = height;
   glViewport(0, 0, width, height);
}

//El constructor de la clase Engine
Engine::Engine(int window_width, int window_heigth): sprites(std::vector<Sprite*>()){
   //Esta parte inicializa glfw
   glfwInit();     
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

   //Esta parte se encarga de inicializar la ventana 
   w_width = window_width;
   w_heigth = window_heigth;

   _window = glfwCreateWindow(w_width, w_heigth, "Tetris", NULL, NULL);
   
   if (_window == NULL)
   {
      std::cout << "Failed to create a window" << std::endl;
      glfwTerminate();
      return;
   }

   glfwMakeContextCurrent(_window);

   //Inicializa GLAD
   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return;
   }

   //Establece el viewport 
   glViewport(0, 0, w_width, w_heigth);
   glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

   //Procesamiento de input
   glfwSetWindowUserPointer(this->_window, this);

   glfwSetKeyCallback(this->_window, Engine::key_callback_static);

   text = gltCreateText(); 
   gltSetText(text, "HOLA MUNDO");
};

//inicializa el bucle de renderizado
void Engine::Init(){
   glfwMakeContextCurrent(_window);

   // Inicializa el contador de fotogramas
   int frameCount = 0;

   // Inicializa el temporizador para medir el tiempo transcurrido
   auto startTime = std::chrono::high_resolution_clock::now();

   while(!glfwWindowShouldClose(_window))
   {
      if (!pause_thread)
      {
         update();
         render();
          // Incrementa el contador de fotogramas
         frameCount++;

         // Calcula el tiempo transcurrido desde el inicio
         auto currentTime = std::chrono::high_resolution_clock::now();
         auto deltaTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
   
         // Si ha pasado un segundo, muestra los FPS y reinicia el contador
         if (deltaTime >= 1) {
            double fps = static_cast<double>(frameCount) / deltaTime;
            std::cout << "FPS: " << fps << std::endl;

            // Reinicia el contador y el temporizador
            frameCount = 0;
            startTime = currentTime;
         }
      }
   }

   stopEngine();

   return;
};

//Funcion de renderizado
void Engine::render(){
   if(editing_sprites)
      return;

   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   if (sprites.size() == 0)
   {
      glfwSwapBuffers(_window);
      glfwPollEvents();
      return;
   }

   for (Sprite* sprite : sprites)
   {
      sprite->render(w_width, w_heigth);
   }

   glfwSwapBuffers(_window);
   glfwPollEvents();
}

//procesar el input
void Engine::processInput(int key, int action){
   for (size_t i = 0; i < inputCallBackFunctions.size(); i++) {
      inputCallBackFunctions[i]->processInput(key);
   }
};

void Engine::update(){
   for (int i = 0; i < updateCallBackFunctions.size(); i++){
      updateCallBackFunctions[i]->update();
   }
};

//Añadir un sprite a la lista
Sprite* Engine::addSprite(std::string pathToTexture, float xPos, float yPos, float width, float height){
   editing_sprites = true;
   Sprite* objToAdd = new Sprite(pathToTexture,xPos, yPos, width, height);

   sprites.push_back(objToAdd);

   editing_sprites = false;

   return objToAdd;
}

void Engine::addSprite(Sprite* sprite){
   editing_sprites = true;
   sprites.push_back(sprite);
   editing_sprites = false;
}

//quitar un sprite y eliminarlo
void Engine::removeSprite(Sprite* sprite){
   for (int i = 0; i < sprites.size(); i++){
      if (sprites[i] == sprite){
         editing_sprites = true;
         sprites.erase(sprites.begin() + i);
         delete sprite;
         editing_sprites = false;
         return;
      }
   } 
};

//Parar el engine
void Engine::stopEngine(){
   pauseEngine();
   glfwSetWindowShouldClose(_window, true);

   if (sprites.size() > 0){
      for (Sprite* sprite : sprites)
      {
         delete sprite;
      }
   }

   glfwTerminate();
};

//Crea una texutura
unsigned int Engine::createTexture(std::string pathToTexture)
{
   int texWidth, texHeight, nrChannels;
   stbi_set_flip_vertically_on_load(true);
   unsigned char *data = stbi_load(pathToTexture.c_str(), &texWidth, &texHeight, &nrChannels, 0);

   unsigned int texture = 0; 
   glGenTextures(1, &texture);
    
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
   
   glGenerateMipmap(GL_TEXTURE_2D);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   stbi_image_free(data);

   return texture;
}

//Añade una funcion al call back del input
void Engine::addInputCallBack(IInputSubscriber* inputSubscriber){
   inputCallBackFunctions.push_back(inputSubscriber);
}

//Añade una funcion al call back del update
void Engine::addUpdateCallBack(IUpdateSubscriber* updateSubscriber){
   updateCallBackFunctions.push_back(updateSubscriber);
};

