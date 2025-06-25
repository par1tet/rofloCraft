#include<classes/World.hpp>

World::World(std::vector<Cube*> cubes, Player* player, GLFWwindow* window){
    this->cubes = cubes;
    this->player = player;

    glfwSetWindowUserPointer(window, this);
}

void World::update(float dt){
    this->player->update(dt);
}