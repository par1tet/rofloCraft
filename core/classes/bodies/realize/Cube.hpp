#pragma once

#include<glm/glm.hpp>
#include<glad/glad.h>

class Cube{
public:
    glm::vec3 position;

    Cube(glm::vec3 position);

    void drawCube(GLuint);
};