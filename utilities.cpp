#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>

#include "utilities.hpp"

namespace utilities = chess::utilities;

std::string utilities::load_as_string(std::string_view p_path)
{
    std::ifstream file_stream { p_path.data() };
    
    if (!file_stream)
    {
        std::cerr << "[ERROR]: Cannot open " << p_path << std::endl;
        return "";
    }
    
    std::string result;
    
    while (file_stream.good())
    {
        std::string line;
        std::getline(file_stream, line);
        
        result += (line + "\n");
    }
    
    return result;
}

uint32_t utilities::create_shader(std::string_view p_source, uint32_t p_type) noexcept
{
    auto shader { glCreateShader(p_type) };
    auto source { p_source.data() };
    
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    
    // Check if the shader has been successfully compiled.
    auto success { 0 };
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        auto error_log_length { 0 };
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error_log_length);
        auto error_log { new char[error_log_length] };
        glGetShaderInfoLog(shader, error_log_length, &error_log_length, error_log);
        
        std::cerr << "[ERROR]: Compiliation error for " << p_source << ":\n";
        std::cerr << error_log << "\n\n";
        
        delete[] error_log;
    }
    
    return shader;
}

uint32_t utilities::create_shader_program(uint32_t p_vertex, uint32_t p_fragment)
{
    auto program { glCreateProgram() };
    glAttachShader(program, p_vertex);
    glAttachShader(program, p_fragment);
    glLinkProgram(program);
    
    // Check if the program has been successfully linked.
    auto success { 0 };
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        auto error_log_length { 0 };
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &error_log_length);
        auto error_log { new char[error_log_length] };
        glGetProgramInfoLog(program, error_log_length, &error_log_length, error_log);
        
        std::cerr << "[ERROR]: Link error for " << program << ":\n";
        std::cerr << error_log << "\n\n";
        
        delete[] error_log;
    }
    
    return program;
}