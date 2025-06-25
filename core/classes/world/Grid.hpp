#pragma once

#include<classes/bodies/realize/Cube.hpp>
#include<vector>
#include<string>

struct infoFlat {
    int width, length;
};

class Grid {
public:
    std::vector<Cube*> cubes;

    Grid(std::vector<Cube*> cubes);
    Grid(std::string typeGeneration, infoFlat);
};