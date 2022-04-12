#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>

#include "shaders.hpp"

#include "renderer.hpp"

namespace 
{
    const uint32_t VERTEX_COUNT = 10000;
    
    uint32_t vertex_buffer;
    uint32_t vertex_array;
    uint32_t element_buffer;
    
    uint32_t shader_program;
    
    uint32_t vertex_offset;
    uint32_t element_buffer_offset;
    
    struct vertex_t
    {
        glm::vec2 pos;
        glm::vec2 local_pos; // For drawing circles.
        glm::vec4 color;
        int32_t circle; // Whether or not the vertex is part of a circle.
    };
}

void renderer::init()
{
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * 10000, nullptr, GL_DYNAMIC_DRAW);
    
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 10000, nullptr, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, pos)));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, local_pos)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, color)));
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, circle)));
    glEnableVertexAttribArray(3);
    
    shader_program = shaders::create_shader_program(shaders::create_shader("renderer-shader.vert", GL_VERTEX_SHADER), shaders::create_shader("renderer-shader.frag", GL_FRAGMENT_SHADER));
    
    glUseProgram(shader_program);
    
    glm::mat4 projection = glm::ortho(0.0f, 40.0f, 30.0f, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void renderer::begin()
{
    glBindVertexArray(vertex_array);
    
    vertex_offset = 0;
    element_buffer_offset = 0;
}

void renderer::draw_colored_rectangle(float p_left, float p_up, float p_right, float p_bottom, float p_red, float p_green, float p_blue, float p_alpha)
{
    std::array<vertex_t, 4> vertices;
    
    vertices[0].pos = glm::vec2(p_right, p_up);
    vertices[1].pos = glm::vec2(p_right, p_bottom);
    vertices[2].pos = glm::vec2(p_left, p_bottom);
    vertices[3].pos = glm::vec2(p_left, p_up);
    
    vertices[0].local_pos = glm::vec2(1.0f, 1.0f);
    vertices[1].local_pos = glm::vec2(1.0f, -1.0f);
    vertices[2].local_pos = glm::vec2(-1.0f, -1.0f);
    vertices[3].local_pos = glm::vec2(-1.0f, 1.0f);
    
    for (uint8_t i = 0; i < 4; i++)
    {
        vertices[i].color = glm::vec4(p_red, p_green, p_blue, p_alpha);
        vertices[i].circle = 0;
    }
    
    std::array<uint32_t, 6> indices;
    
    indices[0] = 0 + vertex_offset;
    indices[1] = 1 + vertex_offset;
    indices[2] = 2 + vertex_offset;
    indices[3] = 0 + vertex_offset;
    indices[4] = 3 + vertex_offset;
    indices[5] = 2 + vertex_offset;
    
    glBufferSubData(GL_ARRAY_BUFFER, vertex_offset * sizeof(vertex_t), 4 * sizeof(vertex_t), vertices.data());
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_offset * sizeof(uint32_t), 6 * sizeof(uint32_t), indices.data());
    
    vertex_offset += 4;
    element_buffer_offset += 6;
}

void renderer::end()
{
    glUseProgram(shader_program);
    glDrawElements(GL_TRIANGLES, element_buffer_offset, GL_UNSIGNED_INT, nullptr);
}