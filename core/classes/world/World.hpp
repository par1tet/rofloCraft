#pragma once

#include<classes/bodies/realize/Cube.hpp>
#include<classes/entities/Player.hpp>
#include<classes/world/Grid.hpp>
#include<vector>

class World{
public:
    Player* player;
    std::vector<Grid*> grids;

    World (std::vector<Grid*> grids, Player* player, GLFWwindow* window);

    void update(float dt);
};