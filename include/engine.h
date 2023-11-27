#ifndef SPRITE_H
#define SPRITE_H

#include "include/glm/ext/vector_float2.hpp"
#include "include/rendering/sprite.h"
#include "include/rendering/text.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <vector>

class IUpdateSubscriber{
public:
    virtual void update() = 0;
};

class IInputSubscriber{
public:
    virtual void processInput(int key) = 0;
};

class Engine{
public:
    Engine(int window_width, int window_heigth);

    void Init();
    Sprite* addSprite(std::string pathToTexture,float xPos, float yPos, float width, float heigth);
    void addSprite(Sprite* sprite);
    void removeSprite(Sprite* sprite);
    Text* addText(std::string text, int xPos, int yPos, int height);

    glm::vec2 getWindowSize();
    void stopEngine();
    void pauseEngine() {pause_thread = true;}
    void resumeEngine() {pause_thread = false;}

    void addInputCallBack(IInputSubscriber*);
    void addUpdateCallBack(IUpdateSubscriber*);

    unsigned int createRGBATexture(std::string pathToTexture);
    unsigned int createRGBTexture(std::string pathToTexture);

    bool isClosed(){ return glfwWindowShouldClose(_window);};

private: 
    std::vector<Sprite*> sprites;
    std::vector<Text*> texts;

    Sprite* background;

    bool editing_sprites = false;
    bool pause_thread = false;

    GLFWwindow* _window; 

    void processInput(int key, int action);
    void render();
    void update();

    std::vector<IInputSubscriber*> inputCallBackFunctions;
    std::vector<IUpdateSubscriber*> updateCallBackFunctions;

    static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (engine)
        {
            engine->processInput(key, action);
        }
    }        
};
#endif
