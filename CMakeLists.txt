cmake_minimum_required(VERSION 3.13)

project(chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(GLFW)

# GLAD
add_library(glad STATIC deps/glad/src/glad.c)
target_include_directories(glad PRIVATE deps/glad/include)

add_executable(
    chess
    
    board.cpp 
    main.cpp
    window.cpp 
    
    window.hpp 
    board.hpp
)

target_link_libraries(chess GLFW::GLFW glad)

target_include_directories(chess PRIVATE ${GLFW_INCLUDE_DIR} deps/glad/include deps/glm)