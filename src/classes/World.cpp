#include<classes/World.hpp>

World::World(std::vector<Cube*> cubes, GLFWwindow* window){
    this->cubes = cubes;
    this->player = new Player(glm::vec3(0,0,3.f), window);

    glfwSetWindowUserPointer(window, this);
}

void World::update(float dt){
    this->player->update(dt);
}