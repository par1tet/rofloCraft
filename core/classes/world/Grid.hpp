#pragma once

#include<classes/bodies/realize/Cube.hpp>
#include<vector>

class Grid {
public:
    std::vector<Cube*> cubes;

    Grid(std::vector<Cube*> cubes);
};