#include<classes/entities/Player.hpp>
#include<GLFW/glfw3.h>
#include<iostream>
#include<classes/World.hpp>

Player::Player(glm::vec3 position, GLFWwindow* window, glm::vec3 size){
    this->position = position;
    this->acceleration = {0.f, -9.8f, 0.f};
    this->speed = glm::vec3{0.f};

    this->camera = new Camera(position, window);
    this->window = window;

    this->size = size;

    glfwSetKeyCallback(window, this->keyCallbackDispatcher);
}

void Player::update(float dt){
    float cameraSpeed = 0.06;
    glm::vec3 delY = glm::vec3{1.f,0.f,1.f};

    if(this->keys['W']){
        this->position += cameraSpeed * glm::normalize(this->camera->direction * delY);
    }
    if(this->keys['S']){
        this->position -= cameraSpeed * glm::normalize(this->camera->direction * delY);
    }
    if(this->keys['A']){
        this->position -= glm::normalize(glm::cross(this->camera->direction, this->camera->upVector)) * cameraSpeed;
    }
    if(this->keys['D']){
        this->position += glm::normalize(glm::cross(this->camera->direction, this->camera->upVector)) * cameraSpeed;
    }

    this->position += this->speed * dt;
    this->speed += this->acceleration * dt;

    this->checkCollision();

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

void Player::checkCollision(){
    World* world = static_cast<World*>(glfwGetWindowUserPointer(this->window));
    std::vector<Cube*>* cubes = &(world->cubes);
        
    if (world){
        collisionInfo cI = this->detectCollision(*cubes);

        if(cI.index != -1){
            this->separateCollision(*cubes, cI);
            this->impulseResolveCollision(*cubes, cI);
            std::cout << "collision" << std::endl;

            cI = this->detectCollision(*cubes);
        }
    }
}

collisionInfo Player::detectCollision(std::vector<Cube*> cubes){
    for(int i = 0; i != cubes.size();i++){
        glm::vec3 position1 = this->position;
        glm::vec3 position2 = cubes[i]->position;
        glm::vec3 size1 = this->size;
        glm::vec3 size2 = cubes[i]->position;

        std::vector<glm::vec3> diaFirst = {
            (position1 - (glm::vec3{size1.x / 2.f, size1.y * 0.9f, size1.z / 2.f})),
            (position1 + (glm::vec3{size1.x / 2.f, size1.y * 0.2f, size1.z / 2.f})),
        };

        std::vector<glm::vec3> diaSecond = {
            (position2 - (size2 / 2.0f)),
            (position2 + (size2 / 2.0f)),
        };

        glm::vec3 overlap = glm::min(diaFirst[1], diaSecond[1]) - glm::max(diaFirst[0], diaSecond[0]);

        glm::vec3 dist = position1 - position2;

        glm::vec3 o1 = glm::vec3{1.f};
        glm::vec3 o2 = glm::vec3{1.f};

        for(int i = 0;i != 3;i++){
            if(diaFirst[1][i]*diaFirst[1][i] < diaFirst[0][i]*diaFirst[0][i]){
                o1[i] = diaFirst[1][i];
                o2[i] = diaSecond[0][i];
            }else{
                o1[i] = diaFirst[0][i];
                o2[i] = diaSecond[1][i];
            }
        }

        glm::vec3 myOverl = o1 - o2;

        int minIndex;
        float minX = glm::min(glm::min(myOverl.x*myOverl.x, myOverl.y*myOverl.y), myOverl.z*myOverl.z);

        std::cout << minX << std::endl;

        for(int i = 0;i != 3;i++){
            if(myOverl[i]*myOverl[i] - 0.01 <= minX && myOverl[i]*myOverl[i] + 0.01 >= minX){
                minIndex = i;
                break;
            }
        }

        std::cout << minIndex << std::endl;

        std::cout << "x: " << position1.x << " y: " << position1.y << " z: " << position1.z << std::endl;
        std::cout << "x: " << position2.x << " y: " << position2.y << " z: " << position2.z << std::endl;
        std::cout << "x: " << overlap.x << " y: " << overlap.y << " z: " << overlap.z << std::endl;
        std::cout << "x: " << myOverl.x << " y: " << myOverl.y << " z: " << myOverl.z << std::endl;

        if ((diaFirst[1][0] >= diaSecond[0][0] && diaSecond[1][0] >= diaFirst[0][0]) &&
            (diaFirst[1][1] >= diaSecond[0][1] && diaSecond[1][1] >= diaFirst[0][1]) &&
            (diaFirst[1][2] >= diaSecond[0][2] && diaSecond[1][2] >= diaFirst[0][2])){
                return {i, myOverl, minIndex};
        }
    }

    return {-1, glm::vec3{0.f}, 0};
}

void Player::separateCollision(std::vector<Cube*> cubes, collisionInfo cI){
    std::cout << cI.overlap[cI.indexMinOverlap] << std::endl;
    this->position[cI.indexMinOverlap] -= cI.overlap[cI.indexMinOverlap];
}

void Player::impulseResolveCollision(std::vector<Cube*> cubes, collisionInfo cI){
    this->speed[cI.indexMinOverlap] = 0.f;
}