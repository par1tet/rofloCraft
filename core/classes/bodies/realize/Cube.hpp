#pragma once

#include<glm/glm.hpp>
#include<glad/glad.h>

class Cube{
public:
    glm::vec3 position, size;

    Cube(glm::vec3 position, glm::vec3 size = glm::vec3{1.f});

    void drawCube(GLuint);
};