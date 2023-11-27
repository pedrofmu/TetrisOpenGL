#include "include/rendering/text.h"

#include "include/glm/ext/vector_float2.hpp"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

#include "include/rendering/stb_image.h"
#include "include/myLibs/hashMap.h"

#include <exception>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

HashMap<char, glm::vec2> dic = {
   {' ', glm::vec2(15, 6)},
   {'0', glm::vec2(15, 5)},
   {'1', glm::vec2(0, 4)},
   {'2', glm::vec2(1, 4)},
   {'3', glm::vec2(2, 4)},
   {'4', glm::vec2(3, 4)},
   {'5', glm::vec2(4, 4)},
   {'6', glm::vec2(5, 4)},
   {'7', glm::vec2(6, 4)},
   {'8', glm::vec2(7, 4)},
   {'9', glm::vec2(8, 4)},
   {'A', glm::vec2(0, 3)},
   {'B', glm::vec2(1, 3)},
   {'C', glm::vec2(2, 3)},
   {'D', glm::vec2(3, 3)},
   {'E', glm::vec2(4, 3)},
   {'F', glm::vec2(5, 3)},
   {'G', glm::vec2(6, 3)},
   {'H', glm::vec2(7, 3)},
   {'I', glm::vec2(8, 3)},
   {'J', glm::vec2(9, 3)},
   {'K', glm::vec2(10, 3)},
   {'L', glm::vec2(11, 3)},
   {'M', glm::vec2(12, 3)},
   {'N', glm::vec2(13, 3)},
   {'O', glm::vec2(14, 3)},
   {'P', glm::vec2(15, 3)},
   {'Q', glm::vec2(0, 2)},
   {'R', glm::vec2(1, 2)},
   {'S', glm::vec2(2, 2)},
   {'T', glm::vec2(3, 2)},
   {'U', glm::vec2(4, 2)},
   {'V', glm::vec2(5, 2)},
   {'W', glm::vec2(6, 2)},
   {'X', glm::vec2(7, 2)},
   {'Y', glm::vec2(8, 2)},
   {'Z', glm::vec2(9, 2)},
};

Text::Text(std::string initialText, int startX , int startY ,int startHeight, unsigned int bitmapFont): shader(Shader("../assets/shader/textShader.vs", "../assets/shader/textShader.fs")){
   float vertices[] = {
      0.5,  0.5, 1.0f, 1.0f,        // top right
      0.5, -0.5, 1.0f, 0.0f,        // bottom right
      -0.5, -0.5, 0.0f, 0.0f,       // bottom left
      -0.5,  0.5, 0.0f, 1.0f        // top left 
   };

   unsigned int indices[] = {
      0, 1, 3,
      1, 2, 3  
   };

   text = initialText; 

   unsigned int vao, vbo, ebo;

   //Crea el VAO VBO y EBO
   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);
   glGenBuffers(1, &ebo);

   glBindVertexArray(vao);

   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
   glEnableVertexAttribArray(1);

   for (int i = 0; i < text.size(); i++){
      if (!dic.HasKey(text[i]))
         throw std::invalid_argument("No existe esa caracter");

      Character character = Character{ .VAO = vao, .VBO = vbo, .EBO = ebo };
      characters.push_back(character);
   }

   texture = bitmapFont;

   x = startX;
   y = startY;

   heigth = startHeight; 
}

Text::~Text(){
   glDeleteBuffers(1, &characters[0].VBO);
   glDeleteBuffers(1, &characters[0].EBO);
   glDeleteVertexArrays(1, &characters[0].VAO);

   glDeleteProgram(shader.ID);
   glDeleteTextures(1, &texture);     
}

void Text::render(float w_width, float w_height){
   glm::mat4 matrix = glm::mat4(1.0f);
   //Escala
   matrix[0][0] = heigth;
   matrix[1][1] = heigth;

   //Posicion
   matrix[3][0] = x;
   matrix[3][1] = y;

   shader.use();

   unsigned int xCharactersLoc = glGetUniformLocation(shader.ID, "xCharacters");
   glUniform1f(xCharactersLoc, 16);

   unsigned int yCharactersLoc = glGetUniformLocation(shader.ID, "yCharacters");
   glUniform1f(yCharactersLoc, 8);

   for (int i = 0; i < characters.size(); i++){
      glBindTexture(GL_TEXTURE_2D, texture);
      glBindVertexArray(characters[i].VAO);

      //Cambiar la posicion
      matrix[3][0] = matrix[3][0] + matrix[0][0];
      
      //Normalizar la matrix
      glm::mat4 normalizedMatrix = matrix;
      normalizedMatrix[3][0] = (normalizedMatrix[3][0] / (w_width * 0.5)) - 1.0;
      normalizedMatrix[3][1] = (normalizedMatrix[3][1] / (w_height * 0.5)) - 1.0;

      normalizedMatrix[0][0] = normalizedMatrix[0][0] / (w_width * 0.5);
      normalizedMatrix[1][1] = normalizedMatrix[1][1] / (w_height * 0.5);
      
      //Pasar el uniform
      unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(normalizedMatrix));

      unsigned int indexXLoc = glGetUniformLocation(shader.ID, "indexX");
      glUniform1f(indexXLoc, dic[text[i]].x);

      unsigned int indexYLoc = glGetUniformLocation(shader.ID, "indexY");
      glUniform1f(indexYLoc, dic[text[i]].y);

      //Dibujar
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
   }
}

void Text::setText(std::string newText){
   if (text.size() == newText.size()){
      text = newText;
   }else{
      unsigned int vao, vbo, ebo;  

      vao = characters[0].VAO;
      vbo = characters[0].VBO;
      ebo = characters[0].EBO;

      characters.clear();

      for (int i = 0; i < newText.size(); i++){
         Character character = Character{ .VAO = vao, .VBO = vbo, .EBO = ebo };
         characters.push_back(character);  
      }

      text = newText;
   }
}
