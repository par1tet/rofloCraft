#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<constants.h>

class Camera{
public:
    glm::vec3 position, direction, upVector;
    glm::mat4 viewMatrix;
    double lastX, lastY;
    double yaw, pitch;
    double sens;

    Camera(glm::vec3 position, GLFWwindow* window);
    void dirHandler(double xpos, double ypos);
    static void keyCallbackDispatcherMouse(GLFWwindow* window, double xpos, double ypos);
    void update();
};
