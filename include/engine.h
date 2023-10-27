#include "include/glm/ext/vector_float2.hpp"
#include "include/rendering/sprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Engine{
public:
    Engine(int window_width, int window_heigth);

    void Init();
    Sprite* addSprite(std::string pathToTexture,float xPos, float yPos, float width, float heigth);
    void addSprite(Sprite* sprite);

    glm::vec2 getWindowSize();
    void stopEngine();

    void addInputCallBack(void(*functionCallBack) (int, int));

private: 
    std::vector<Sprite*> sprites;
    GLFWwindow* _window; 
    bool editing_sprites = false;

    void processInput(int key, int action);
    void render();

    std::vector<void(*) (int, int)> inputCallBackFunctions;

    static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (engine)
        {
            engine->processInput(key, action);
        }
    }        
};


