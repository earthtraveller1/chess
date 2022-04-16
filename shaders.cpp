#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <string>

#include "shaders.hpp"

namespace shaders
{
    uint32_t create_shader(std::string_view p_path, uint32_t p_type)
    {
        std::ifstream file_stream(p_path.data());
        
        if (!file_stream)
        {
            std::cerr << "[ERROR]: Failed to open " << p_path << std::endl;
            return 0;
        }
        
        std::string source;
        
        while (file_stream.good())
        {
            std::string line;
            std::getline(file_stream, line);
            source += line += '\n';
        }
        
        file_stream.close();
        
        const char* source_c_str = source.c_str();
        
        uint32_t shader = glCreateShader(p_type);
        glShaderSource(shader, 1, &source_c_str, nullptr);
        glCompileShader(shader);
        
        return shader;
    }
    
    uint32_t create_shader_program(uint32_t p_vertex, uint32_t p_fragment)
    {
        uint32_t program = glCreateProgram();
        glAttachShader(program, p_vertex);
        glAttachShader(program, p_fragment);
        glLinkProgram(program);
        
        return program;
    }
}