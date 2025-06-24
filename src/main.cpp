#include<string>
#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <utils/shader_utils.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<classes/bodies/realize/Cube.hpp>
#include <constants.h>
#include<classes/camera/Camera.hpp>
#include<classes/entities/Player.hpp>
#include<classes/World.hpp>

int main(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "ROFLO CRAFT WWW", nullptr, nullptr);

    if (window == nullptr){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }

    GLuint shaderProgram = createShaderProgram(
      	std::string(std::string(CMAKE_SOURCE_PATH) + "shaders/vertex_shader.glsl").c_str(),
      	std::string(std::string(CMAKE_SOURCE_PATH) + "shaders/fragment_shader.glsl").c_str()
    );    

    int width, heigth;
    glfwGetFramebufferSize(window, &width, &heigth);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0,0, width, heigth);

    glEnable(GL_DEPTH_TEST);
    
    std::vector<Cube*> cubes = {
        new Cube(glm::vec3{0})
    };

    World* world = new World(cubes, window);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.1, 0.6, 0.8, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        system("clear");

        GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelM");

        glm::mat4 projection = glm::mat4(1);
        projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / HEIGHT, 0.1f, 1000.0f);
        GLuint projLoc = glGetUniformLocation(shaderProgram, "projM");

        world->update(1/60);
        GLuint viewLoc = glGetUniformLocation(shaderProgram, "viewM");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(world->player->camera->viewMatrix));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        for(int i = 0;i != cubes.size();i++){
            glm::mat4 model = glm::mat4(1);
            model = glm::translate(model, world->cubes[i]->position);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            cubes[i]->drawCube(shaderProgram);
        }

        glfwSwapBuffers(window);
    }

    return 0;
}
