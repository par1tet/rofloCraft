#include <classes/camera/Camera.hpp>
#include <iostream>
#include <classes/World.hpp>
#include <glad/glad.h>

Camera::Camera(glm::vec3 position, GLFWwindow* window){
    this->position = position;

    this->lastX = WIDTH / 2;
    this->lastY = HEIGHT / 2;

    this->yaw = -90.f;
    this->pitch = 0.f;
    this->sens = 0.05;

    glm::vec3 front;

    front.x = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
    front.y = sin(glm::radians(this->pitch));
    front.z = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));

    this->direction = glm::normalize(front);
    this->upVector = glm::vec3(0,1,0);

    this->viewMatrix = glm::lookAt(this->position, this->position + this->direction, this->upVector);

    glfwSetCursorPosCallback(window, this->keyCallbackDispatcherMouse);
}

void Camera::update(){
    GLfloat cameraSpeed = 0.4f;
    
    glm::vec3 front;
    front.x = cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
    front.y = sin(glm::radians(this->pitch));
    front.z = cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));
    this->direction = glm::normalize(front);

    this->viewMatrix = glm::lookAt(this->position, this->position + this->direction, this->upVector);
}

void Camera::keyCallbackDispatcherMouse(GLFWwindow* window, double xpos, double ypos){
    World* world = static_cast<World*>(glfwGetWindowUserPointer(window));
        
    if (world) {
        world->player->camera->dirHandler(xpos, ypos);
    }
}

void Camera::dirHandler(double xpos, double ypos){
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    this->lastX = xpos;
    this->lastY = ypos;

    xoffset *= this->sens;
    yoffset *= this->sens;     

    this->yaw += xoffset;
    this->pitch += yoffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
}