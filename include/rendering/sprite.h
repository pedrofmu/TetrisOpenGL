#ifndef OBJETO_H
#define OBJETO_H

#include "include/glm/fwd.hpp"
#include "include/rendering/shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

class Sprite {
public:
    Sprite(std::string pathToTexture, float X, float Y, float WIDTH, float HEIGTH);
    ~Sprite();

    void render(int w_width, int w_heigth);
    void setPosition(float nX, float nY);
    void setScale(float n_width, float n_heigth);
    void setRotation(float n_rotation);

    glm::vec2 getPosition();
    glm::vec2 getScale();
    float getRotation();
private:
    unsigned int VAO, VBO, EBO, texture;
    Shader shader;

    glm::mat4 matrix, rotationMatrix;
    float xPos, yPos;
    float width, heigth;
    float rotation;
};

#endif // OBJETO_H

