cmake_minimum_required(VERSION 3.13)

project(chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

option(CMAKE_WIN32_EXECUTABLE "Make the executables a Win32 executable rather than a traditional console app" OFF)

# Give executables on Linux the .out extension
if (UNIX)
    set(CMAKE_EXECUTABLE_SUFFIX .out)
endif()

# Use the highest warning levels possible
if (MSVC)
    add_compile_options(/Wall)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Use full paths whenever possible
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fdiagnostics-absolute-paths)
    add_link_options(-fdiagnostics-absolute-paths)
endif()

find_package(GLFW)

# GLAD
add_library(glad STATIC deps/glad/src/glad.c)
target_include_directories(glad PRIVATE deps/glad/include)

if (UNIX AND NOT APPLE)
    target_link_libraries(glad dl)
endif()

if (WIN32)
    option(CHESS_USE_WWINMAIN "Use wWinMain instead of main as the entry point" ON)
    if (CHESS_USE_WWINMAIN)
        set(CHESS_EXECUTABLE_TYPE WIN32)
    endif()
endif()

add_executable(
    chess ${CHESS_EXECUTABLE_TYPE}
    
    stb-image.c 
    
    application.cpp 
    board.cpp 
    game-scene.cpp 
    main.cpp 
    menu-scene.cpp 
    move-checker.cpp
    option-loader.cpp
    piece-manager.cpp 
    renderer.cpp 
    utilities.cpp 
    window.cpp 
    
    application.hpp 
    board.hpp 
    game-scene.hpp 
    menu-scene.hpp 
    move-checker.hpp
    option-loader.hpp
    piece-manager.hpp 
    renderer.hpp 
    scene-manager.hpp 
    scene.hpp 
    utilities.hpp 
    window.hpp 
)

target_link_libraries(chess GLFW::GLFW glad)

target_include_directories(chess PRIVATE ${GLFW_INCLUDE_DIR} deps/glad/include deps/glm deps/stb)