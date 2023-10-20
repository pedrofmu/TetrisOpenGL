#include "include/objeto.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Engine{
public:
    Engine();
    void Init();
    Objeto añadirObjeto(std::string pathToTexture, float width, float heigth, float xPos, float yPos);

    std::vector<Objeto> objetos;

private: 
    GLFWwindow* _window; 
    void render();
};
