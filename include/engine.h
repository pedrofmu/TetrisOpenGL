#include "include/rendering/sprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Engine{
public:
    Engine();
    void Init();
    Sprite añadirSprite(std::string pathToTexture,float xPos, float yPos, float width, float heigth);

    std::vector<Sprite> sprites;

private: 
    GLFWwindow* _window; 
    void render();
};
