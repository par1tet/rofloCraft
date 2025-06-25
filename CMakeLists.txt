cmake_minimum_required(VERSION 3.18)
project(rofloCraft VERSION 0.1.0)

add_executable(rofloCraft
    src/main.cpp
    utils/shader_utils.cpp
    src/classes/bodies/realize/Cube.cpp
    src/classes/camera/Camera.cpp
    src/classes/entities/Player.cpp
    src/classes/world/World.cpp
    src/classes/world/Grid.cpp
)

include(FetchContent)
FetchContent_Declare(soil2  
    GIT_REPOSITORY https://github.com/SpartanJ/SOIL2  
    GIT_TAG master  
)  
FetchContent_MakeAvailable(soil2)

add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

target_include_directories(rofloCraft PRIVATE
    ${CMAKE_SOURCE_DIR}/core
)

target_include_directories(rofloCraft PRIVATE  
    ${soil2_SOURCE_DIR}/src  
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(rofloCraft PRIVATE soil2 glad glfw OpenGL::GL glm::glm)
target_compile_definitions(rofloCraft PRIVATE CMAKE_SOURCE_PATH="${CMAKE_SOURCE_DIR}/")
