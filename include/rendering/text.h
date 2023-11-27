#ifndef TEXT
#define TEXT

#include "include/rendering/shader.h"
#include <stdio.h>
#include <string>
#include <vector>

struct Character{
   unsigned int VAO;
   unsigned int VBO;
   unsigned int EBO;
};
   
class Text{
public:
   Text(std::string initialText,int startX , int startY,int startHeight ,unsigned int bitmapFont);
   ~Text();

   void setText(std::string newText);

   void render(float width, float height);

   int x, y;
   int heigth;
private:
   std::string text;
   Shader shader;
   unsigned int texture;

   std::vector<Character> characters;
};

#endif 
