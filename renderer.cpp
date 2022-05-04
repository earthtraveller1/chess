#include <glad/glad.h>
#include <glm/glm.hpp>

#include "utilities.hpp"

#include "renderer.hpp"

using chess::renderer_t;

renderer_t::renderer_t(uint32_t p_max_quads): 
    m_max_number_of_quads(p_max_quads)
{
    auto vertex_shader { utilities::create_shader("renderer-shader.vert", GL_VERTEX_SHADER) };
    auto fragment_shader { utilities::create_shader("renderer-shader.frag", GL_FRAGMENT_SHADER) };
    
    m_shader_program = utilities::create_shader_program(vertex_shader, fragment_shader);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_max_number_of_quads * sizeof(vertex_t) * 4, nullptr, GL_DYNAMIC_DRAW);
    
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_max_number_of_quads * 6 * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, position)));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, position)));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, position)));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, position)));
    glEnableVertexAttribArray(0);
}