#include "include/rendering/tileSprite.h"
#include "include/rendering/sprite.h"
#include "include/rendering/stb_image.h"

TileSprite::TileSprite(unsigned int defaultTexture, float X, float Y, float WIDTH, float HEIGTH): Sprite(){
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

   //Crea el VAO VBO y EBO
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
   glEnableVertexAttribArray(1);

   //Texture
   texture = defaultTexture;

   //Crear matriz
   matrix = glm::mat4(1.0f);

   xPos = X;
   yPos = Y;

   width = WIDTH;
   heigth = HEIGTH;

   matrix = glm::translate(matrix, glm::vec3(xPos, yPos, 0));
   
   matrix[0][0] = matrix[0][0] * WIDTH;
   matrix[1][1] = matrix[1][1] * heigth;

   rotationMatrix = glm::mat4(1.0f);
};

void TileSprite::setTexutre(unsigned int newTexture){
   texture = newTexture;
};
