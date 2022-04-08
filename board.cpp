#include <glad/glad.h>

#include <cstdint>
#include <vector>
#include <array>
#include <string_view>
#include <fstream>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "board.hpp"

namespace 
{
    struct vertex_t
    {
        glm::vec2 position;
        glm::vec3 color;
    };
    
    uint32_t vertex_array = 0;
    uint32_t vertex_buffer = 0;
    uint32_t index_buffer = 0;
    
    uint32_t index_count = 0;
    
    uint32_t shader_program = 0;
    
    glm::mat4 model;
    glm::mat4 projection;
    
    std::vector<vertex_t> generate_board_vertices()
    {
        float x_offset = 0.0f;
        float y_offset = 0.0f;
        
        enum color_e
        {
            light, dark
        } color = color_e::light;
        
        std::vector<vertex_t> vertices;
        
        for (uint8_t i = 0; i < 8; i++)
        {
            for (uint8_t j = 0; j < 8; j++)
            {
                std::array<vertex_t, 4> square_vertices;
                
                square_vertices[0].position = glm::vec2(x_offset + 1.0f, y_offset);
                square_vertices[1].position = glm::vec2(x_offset + 1.0f, y_offset + 1.0f);
                square_vertices[2].position = glm::vec2(x_offset, y_offset + 1.0f);
                square_vertices[3].position = glm::vec2(x_offset, y_offset);
                
                if (color == color_e::light)
                {
                    for (uint8_t k = 0; k < 4; k++)
                    {
                        square_vertices[k].color = glm::vec3(0.97f, 0.9f, 0.9f);
                    }
                    color = color_e::dark;
                } else if (color == color_e::dark)
                {
                    for (uint8_t k = 0; k < 4; k++)
                    {
                        square_vertices[k].color = glm::vec3(0.17f, 0.1f, 0.1f);
                    }
                    color = color_e::light;
                }
                
                for (vertex_t vertex: square_vertices)
                {
                    vertices.emplace_back(vertex);
                }
                
                x_offset += 1.0f;
            }
            
            y_offset += 1.0f;
            x_offset = 0.0f;
            
            if (color == color_e::light)
            {
                color = color_e::dark;
            }
            else 
            {
                color = color_e::light;
            }
        }
        
        return vertices;
    }
    
    std::vector<uint32_t> generated_board_indices()
    {
        std::vector<uint32_t> indices;
        
        uint16_t offset = 0;
        
        for (uint8_t i = 0; i < 64; i++)
        {
            indices.push_back(0 + offset);
            indices.push_back(1 + offset);
            indices.push_back(2 + offset);
            indices.push_back(0 + offset);
            indices.push_back(3 + offset);
            indices.push_back(2 + offset);
            
            offset += 4;
            index_count += 6;
        }
        
        return indices;
    }
    
    void initialize_vertex_data()
    {
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        std::vector<vertex_t> vertices = generate_board_vertices();

        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex_t), vertices.data(), GL_STATIC_DRAW);

        std::vector<uint32_t> indices = generated_board_indices();

        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void *>(offsetof(vertex_t, position)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void *>(offsetof(vertex_t, color)));
        glEnableVertexAttribArray(1);
    }
    
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

void board::init()
{
    model = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, 40.0f, 30.0f, 0.0f, 0.0f, 100.0f);
    
    model = glm::translate(model, glm::vec3((40.0f - (8.0f * 2.5f)) / 2.0f, (30.0f - (8.0f * 2.5f)) / 2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.5f));
    
    uint32_t vertex_shader = create_shader("board-shader.vert", GL_VERTEX_SHADER);
    uint32_t fragment_shader = create_shader("board-shader.frag", GL_FRAGMENT_SHADER);
    
    shader_program = create_shader_program(vertex_shader, fragment_shader);
    
    initialize_vertex_data();
}

void board::render()
{
    glUseProgram(shader_program);
    
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    glBindVertexArray(vertex_array);
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}