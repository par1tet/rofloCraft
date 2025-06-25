#include<classes/world/Grid.hpp>
#include<cmath>

Grid::Grid(std::vector<Cube*> cubes){
    this->cubes = cubes;
}

Grid::Grid(std::string typeGeneration, infoFlat iF){
    std::vector<Cube*> generateCubes = {};

    for(int i = -(ceil(iF.width / 2));i != (floor(iF.width / 2));i++){
        for(int k = -(ceil(iF.length / 2));k != (floor(iF.length / 2));k++){
            generateCubes.push_back(new Cube(glm::vec3{0.f + i, 0, 0.f + k}));
        }
    }

    this->cubes = generateCubes;
}