#pragma once

#include<glm/glm.hpp>
#include<classes/camera/Camera.hpp>
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>

class Player{
public:
    glm::vec3 position;
    Camera* camera;
    bool keys[255]{false};

    Player(glm::vec3 position, GLFWwindow*);

    void moveHandler(int key, int action);
    static void keyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods);
    void update(float dt);
};