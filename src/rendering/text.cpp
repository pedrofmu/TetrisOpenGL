#include "include/rendering/text.h"

#include "include/rendering/stb_image.h"

#include <stdio.h>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



Text::Text(std::string initialText): shader(Shader("../assets/shader/textShader.vs", "../assets/shader/textShader.fs")){
   float vertices[] = {
      0.5,  0.5,         // top right
      0.5, -0.5,         // bottom right
      -0.5, -0.5,        // bottom left
      -0.5,  0.5,        // top left 
   };
   
   unsigned int indices[] = {
      0, 1, 3,
      1, 2, 3  
   };

   text = initialText; 

   unsigned int vao, vbo, ebo;

   // Generar los indices
   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);
   glGenBuffers(1, &ebo);

   glBindVertexArray(vao);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   // Configurar el atributo de posición de los vértices
   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   for (int i = 0; i < text.size(); i++){
      Character character = Character{ .VAO = vao, .VBO = vbo, .EBO = ebo };
      characters.push_back(character);
   }

   texture = 0;
}

void Text::render(){
   shader.use();

   for (int i = 0; i < characters.size(); i++){
      glBindVertexArray(characters[i].VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
   }
}
