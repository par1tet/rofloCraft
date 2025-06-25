#include<classes/world/World.hpp>

World::World(std::vector<Grid*> grids, Player* player, GLFWwindow* window){
    this->grids = grids;
    this->player = player;

    glfwSetWindowUserPointer(window, this);
}

void World::update(float dt){
    this->player->update(dt);
}