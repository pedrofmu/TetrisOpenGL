#ifndef OBJETO_H
#define OBJETO_H

#include "include/glm/fwd.hpp"
#include "include/rendering/shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

class Objeto {
public:
    Objeto(std::string pathToTexture, float X, float Y, float WIDTH, float HEIGTH);

    unsigned int VAO, VBO, EBO, texture;
    Shader shader;

    glm::mat4 matrix;
    float xPos, yPos;
    float width, heigth;
};

#endif // OBJETO_H

