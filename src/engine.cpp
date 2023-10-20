#include "include/engine.h"
#include "include/rendering/sprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <include/glm/glm.hpp>
#include <include/glm/gtc/matrix_transform.hpp>
#include <include/glm/gtc/type_ptr.hpp>

//Cambia el viewport segun se redimensione la pantalla
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

Engine::Engine(): sprites(std::vector<Sprite>()){
   //Esta parte inicializa glfw
   glfwInit();     
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   //Esta parte se encarga de inicializar la ventana 
   _window = glfwCreateWindow(800, 600, "Tetris", NULL, NULL);
   
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
   glViewport(0, 0, 800, 600);
   glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
};

void Engine::Init(){
   while(!glfwWindowShouldClose(_window))
   {
      render(); 
   }

   glfwTerminate();
};

void Engine::render(){
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   for (int i = 0; i < sprites.size(); i++)
   {
      sprites[i].shader.use();
      
      glBindTexture(GL_TEXTURE_2D, sprites[i].texture);
      glBindVertexArray(sprites[i].VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);

      unsigned int transformLoc = glGetUniformLocation(sprites[i].shader.ID, "transform");
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(sprites[i].matrix));
   }

   glfwSwapBuffers(_window);
   glfwPollEvents();
}

Sprite Engine::añadirSprite(std::string pathToTexture, float width, float height, float xPos, float yPos){
   Sprite objToAdd = Sprite(pathToTexture,width, height, xPos, yPos);

   sprites.insert(sprites.end(), objToAdd);

   return objToAdd;
}

