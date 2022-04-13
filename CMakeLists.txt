cmake_minimum_required(VERSION 3.13)

project(chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

# Give executables on Linux the .out extension
if (UNIX)
    set(CMAKE_EXECUTABLE_SUFFIX .out)
endif()

find_package(GLFW)

# GLAD
add_library(glad STATIC deps/glad/src/glad.c)
target_include_directories(glad PRIVATE deps/glad/include)

if (UNIX AND NOT APPLE)
    target_link_libraries(glad dl)
endif()

add_executable(
    chess
    
    board.cpp 
    main.cpp
    pieces.cpp
    renderer.cpp
    shaders.cpp
    window.cpp 
    
    board.hpp
    pieces.hpp
    renderer.hpp
    shaders.hpp
    window.hpp 
)

target_link_libraries(chess GLFW::GLFW glad)

target_include_directories(chess PRIVATE ${GLFW_INCLUDE_DIR} deps/glad/include deps/glm)