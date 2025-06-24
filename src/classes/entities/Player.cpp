#include<classes/entities/Player.hpp>
#include<GLFW/glfw3.h>
#include<iostream>
#include<classes/World.hpp>

Player::Player(glm::vec3 position, GLFWwindow* window){
    this->position = position;

    this->camera = new Camera(position, window);

    glfwSetKeyCallback(window, this->keyCallbackDispatcher);
}

void Player::update(float dt){
    float cameraSpeed = 0.06;

    std::cout << this->keys['W'] << std::endl;
    if(this->keys['W']){
        this->position += cameraSpeed * this->camera->direction;
    }
    if(this->keys['S']){
        this->position -= cameraSpeed * this->camera->direction;
    }
    if(this->keys['A']){
        this->position -= glm::normalize(glm::cross(this->camera->direction, this->camera->upVector)) * cameraSpeed;
    }
    if(this->keys['D']){
        this->position += glm::normalize(glm::cross(this->camera->direction, this->camera->upVector)) * cameraSpeed;
    }

    this->camera->position = this->position;
    this->camera->update();
}

void Player::keyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods){
    World* world = static_cast<World*>(glfwGetWindowUserPointer(window));
        
    if (world){
        world->player->moveHandler(key, action);
    }
}

void Player::moveHandler(int key, int action){
    if (action == GLFW_PRESS) {
        this->keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        this->keys[key] = false;
    }
}
