#ifndef SPRITE 
#define SPRITE

#include "include/glm/fwd.hpp"
#include "include/rendering/shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

class Sprite {
public:
    Sprite():shader(Shader("../assets/shader/shader.vs", "../assets/shader/shader.fs")){
        VAO = 0;
        VBO = 0;
        EBO = 0;
        texture = 0;
    };

    Sprite(std::string pathToTexture, float X, float Y, float WIDTH, float HEIGTH);
    ~Sprite();

    void render(int w_width, int w_heigth);

    void setPosition(float nX, float nY);
    void setScale(float n_width, float n_heigth);
    void setRotation(float n_rotation);

    glm::vec2 getPosition();
    glm::vec2 getScale();
    float getRotation();
protected:
    unsigned int VAO, VBO, EBO, texture;
    Shader shader;

    glm::mat4 matrix, rotationMatrix;
    float xPos, yPos;
    float width, heigth;
    float rotation;
};

#endif 
