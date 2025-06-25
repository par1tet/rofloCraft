#pragma once

#include<classes/bodies/realize/Cube.hpp>
#include<classes/entities/Player.hpp>
#include<vector>

class World{
public:
    Player* player;
    std::vector<Cube*> cubes;

    World (std::vector<Cube*> cubes, Player* player, GLFWwindow* window);

    void update(float dt);
};