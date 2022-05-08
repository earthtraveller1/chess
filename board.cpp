#include <glad/glad.h>
#include <array>
#include <iostream>

#include "utilities.hpp"

#include "board.hpp"

using chess::board_t;

namespace 
{
    // Represents a single pixel
    struct pixel_t
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };
    
    // Generate a checkerboard texture.
    std::array<std::array<pixel_t, 8>, 8> generate_board_texture()
    {
        std::array<std::array<pixel_t, 8>, 8> pixels {};
        
        enum class color_e
        {
            LIGHT = 0, DARK = 1
        } color = color_e::LIGHT;
        
        for (auto i { 0 }; i < 8; i++)
        {
            for (auto j { 0 }; j < 8; j += 1)
            {
                switch (color)
                {
                case color_e::LIGHT:
                    pixels[i][j] = { 255, 255, 255 };
                    color = color_e::DARK;
                    break;
                case color_e::DARK:
                    pixels[i][j] = { 0, 0, 0 };
                    color = color_e::LIGHT;
                    break;
                }
            }
            
            color = static_cast<color_e>(!(static_cast<bool>(color)));
        }
        
        return pixels;
    }
}

board_t::board_t()
{
    auto vertex_source { utilities::load_as_string("board-shader.vert") };
    auto fragment_source { utilities::load_as_string("board-shader.frag") };
    
    auto vertex_shader { utilities::create_shader(vertex_source, GL_VERTEX_SHADER) };
    auto fragment_shader { utilities::create_shader(fragment_source, GL_FRAGMENT_SHADER) };
    
    m_shader_program = utilities::create_shader_program(vertex_shader, fragment_shader);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    
    std::array<float, 4 * 4> vertices
    {
        // Positions    // UVs
         1.0f,  1.0f,   1.0f, 0.0f,
         1.0f, -1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f,   0.0f, 1.0f,
        -1.0f,  1.0f,   0.0f, 0.0f
    };
    
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    std::array<uint8_t, 6> indices 
    {
        0, 1, 2,
        0, 3, 2
    };
    
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glUseProgram(m_shader_program);
    glUniform1i(glGetUniformLocation(m_shader_program, "my_texture"), 0);
    
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    auto texture_data { generate_board_texture() };
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, &(texture_data[0][0]));
}

void board_t::render()
{
    glUseProgram(m_shader_program);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
}

board_t::~board_t()
{
    glDeleteProgram(m_shader_program);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteTextures(1, &m_texture);
}