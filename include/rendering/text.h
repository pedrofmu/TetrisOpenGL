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
   Text(std::string initialText);

   void setText(std::string newText);

   void render();
private:
   std::string text;
   Shader shader;
   unsigned int texture;

   std::vector<Character> characters;
};

#endif 
