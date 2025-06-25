#pragma once

#include<glm/glm.hpp>
#include<classes/camera/Camera.hpp>
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<vector>
#include<classes/bodies/realize/Cube.hpp>

struct collisionInfo {
    int index;
    glm::vec3 overlap;
    int indexMinOverlap;
};

class Player{
public:
    glm::vec3 position, speed, acceleration, size;
    Camera* camera;
    bool keys[255]{false};
    GLFWwindow* window;

    Player(glm::vec3 position, GLFWwindow*, glm::vec3 size = {10.f, 2.f, 10.f});

    void moveHandler(int key, int action);
    static void keyCallbackDispatcher(GLFWwindow* window, int key, int scancode, int action, int mods);
    void update(float dt);
    void checkCollision();

    collisionInfo detectCollision(std::vector<Cube*> cubes);
    void separateCollision(std::vector<Cube*> cubes, collisionInfo cI);
    void impulseResolveCollision(std::vector<Cube*> cubes, collisionInfo cI);
};