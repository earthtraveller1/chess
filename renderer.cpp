#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <cmath>

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

void renderer::draw_colored_rectangle(float p_pos_x, float p_pos_y, float p_width, float p_height, float p_red, float p_green, float p_blue, float p_alpha)
{
    std::array<vertex_t, 4> vertices;
    
    vertices[0].pos = glm::vec2(p_width + p_pos_x, p_pos_y);
    vertices[1].pos = glm::vec2(p_width + p_pos_x, p_height + p_pos_y);
    vertices[2].pos = glm::vec2(p_pos_x, p_height + p_pos_y);
    vertices[3].pos = glm::vec2(p_pos_x, p_pos_y);
    
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

void renderer::draw_rotated_colored_rectangle(float p_pos_x, float p_pos_y, float p_width, float p_height, float p_angle, float p_red, float p_green, float p_blue, float p_alpha)
{
    std::array<vertex_t, 4> vertices;
    
    vertices[0].pos = glm::vec2(p_width, 0.0f);
    vertices[1].pos = glm::vec2(p_width, p_height);
    vertices[2].pos = glm::vec2(0.0f, p_height);
    vertices[3].pos = glm::vec2(0.0f, 0.0f);
    
    auto rotation_matrix { glm::mat2(1.0f) };
    rotation_matrix[0][0] = std::cos(glm::radians(p_angle));
    rotation_matrix[0][1] = -std::sin(glm::radians(p_angle));
    rotation_matrix[1][0] = std::sin(glm::radians(p_angle));
    rotation_matrix[1][1] = std::cos(glm::radians(p_angle));
    
    for (auto& vertex: vertices)
    {
        vertex.pos = vertex.pos * rotation_matrix;
        
        vertex.pos.x += p_pos_x;
        vertex.pos.y += p_pos_y;
    }
    
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

void renderer::draw_circle(float p_x, float p_y, float p_radius, float p_red, float p_green, float p_blue, float p_alpha)
{
    renderer::draw_ellipse(p_x, p_y, p_radius, p_radius, p_red, p_green, p_blue, p_alpha);
}

void renderer::draw_ellipse(float p_pos_x, float p_pos_y, float p_width, float p_height, float p_red, float p_green, float p_blue, float p_alpha)
{
    std::array<vertex_t, 4> vertices;
    
    vertices[0].pos = glm::vec2(p_width + p_pos_x, p_pos_y);
    vertices[1].pos = glm::vec2(p_width + p_pos_x, p_height + p_pos_y);
    vertices[2].pos = glm::vec2(p_pos_x, p_height + p_pos_y);
    vertices[3].pos = glm::vec2(p_pos_x, p_pos_y);
    
    vertices[0].local_pos = glm::vec2(1.0f, 1.0f);
    vertices[1].local_pos = glm::vec2(1.0f, -1.0f);
    vertices[2].local_pos = glm::vec2(-1.0f, -1.0f);
    vertices[3].local_pos = glm::vec2(-1.0f, 1.0f);
    
    for (uint8_t i = 0; i < 4; i++)
    {
        vertices[i].color = glm::vec4(p_red, p_green, p_blue, p_alpha);
        vertices[i].circle = 1;
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

void renderer::draw_rotated_ellipse(float p_pos_x, float p_pos_y, float p_width, float p_height, float p_angle, float p_red, float p_green, float p_blue, float p_alpha)
{
    std::array<vertex_t, 4> vertices;
    
    vertices[0].pos = glm::vec2(p_width, 0.0f);
    vertices[1].pos = glm::vec2(p_width, p_height);
    vertices[2].pos = glm::vec2(0.0f, p_height);
    vertices[3].pos = glm::vec2(0.0f, 0.0f);
    
    auto rotation_matrix { glm::mat2(1.0f) };
    rotation_matrix[0][0] = std::cos(glm::radians(p_angle));
    rotation_matrix[0][1] = -std::sin(glm::radians(p_angle));
    rotation_matrix[1][0] = std::sin(glm::radians(p_angle));
    rotation_matrix[1][1] = std::cos(glm::radians(p_angle));
    
    for (auto& vertex: vertices)
    {
        vertex.pos = vertex.pos * rotation_matrix;
        
        vertex.pos.x += p_pos_x;
        vertex.pos.y += p_pos_y;
    }
    
    vertices[0].local_pos = glm::vec2(1.0f, 1.0f);
    vertices[1].local_pos = glm::vec2(1.0f, -1.0f);
    vertices[2].local_pos = glm::vec2(-1.0f, -1.0f);
    vertices[3].local_pos = glm::vec2(-1.0f, 1.0f);
    
    for (uint8_t i = 0; i < 4; i++)
    {
        vertices[i].color = glm::vec4(p_red, p_green, p_blue, p_alpha);
        vertices[i].circle = 1;
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

void renderer::cleanup()
{
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &element_buffer);
    glDeleteVertexArrays(1, &vertex_array);
    
    glDeleteProgram(shader_program);
}