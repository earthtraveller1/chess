#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <iostream>
#include <string>

#include "utilities.hpp"

#include "renderer.hpp"

using chess::renderer_t;
using namespace std::literals::string_literals;

renderer_t::renderer_t(uint32_t p_max_quads): 
    m_max_number_of_quads(p_max_quads),
    m_vertices(m_max_number_of_quads * 4),
    m_vertices_iterator(m_vertices.begin())
{
    auto vertex_shader_source { utilities::load_as_string("renderer-shader.vert") };
    auto fragment_shader_source { utilities::load_as_string("renderer-shader.frag") };
    
    auto vertex_shader { utilities::create_shader(vertex_shader_source, GL_VERTEX_SHADER) };
    auto fragment_shader { utilities::create_shader(fragment_shader_source, GL_FRAGMENT_SHADER) };
    
    m_shader_program = utilities::create_shader_program(vertex_shader, fragment_shader);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_max_number_of_quads * sizeof(vertex_t) * 4, nullptr, GL_DYNAMIC_DRAW);
    
    std::vector<uint32_t> indices(p_max_quads * 6);
    
    // Initialize all the indices.
    for (auto i { 0 }, vertex_offset { 0 }; i < (m_max_number_of_quads * 6); i += 6, vertex_offset += 4)
    {
        indices[i + 0] = vertex_offset + 0;
        indices[i + 1] = vertex_offset + 1;
        indices[i + 2] = vertex_offset + 2;
        indices[i + 3] = vertex_offset + 0;
        indices[i + 4] = vertex_offset + 3;
        indices[i + 5] = vertex_offset + 2;
    }
    
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_max_number_of_quads * 6 * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, position)));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, uv)));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, color)));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(vertex_t), reinterpret_cast<void*>(offsetof(vertex_t, texture)));
    glEnableVertexAttribArray(0);
    
    // Initialize all the textures to 0, as 0 is used to designate the lack of a texture.
    for (auto& texture: m_textures)
    {
        texture = 0;
    }
    
    // Initialize all of the texture uniforms
    glUseProgram(m_shader_program);
    for (auto i { 0 }; i < 32; i++)
    {
        std::string uniform_name { "texture_samplers["s + std::to_string(i) + "]"s };
        auto uniform_location { glGetUniformLocation(m_shader_program, uniform_name.data()) };
        glUniform1i(uniform_location, i);
    }
}

void renderer_t::set_texture(std::string_view p_path, uint8_t p_slot) noexcept
{
    // Delete existing texture in slot if it exists
    if (m_textures[p_slot] != 0)
    {
        glDeleteTextures(1, &(m_textures[p_slot]));
        m_textures[p_slot] = 0;
    }
    
    auto texture { static_cast<uint32_t>(0) };
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    auto width { 0 }, height { 0 }, color_channels { 0 };
    auto pixel_data { stbi_load(p_path.data(), &width, &height, &color_channels, 0) };
    
    if (pixel_data == nullptr)
    {
        std::cerr << "[FATAL ERROR]: Failed to load " << p_path << ".\n";
        return;
    }
    
    auto image_format { static_cast<uint32_t>(0) };
    
    switch (color_channels)
    {
        case 1:
            image_format = GL_RED;
            break;
        case 2:
            image_format = GL_RG;
            break;
        case 3:
            image_format = GL_RGB;
            break;
        case 4:
            image_format = GL_RGBA;
            break;
        default:
            image_format = GL_RGB;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, image_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, pixel_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(pixel_data);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    m_textures[p_slot] = texture;
}

void renderer_t::begin()
{
    m_vertices_iterator = m_vertices.begin();
}

void renderer_t::draw_quad(const quad_t& p_quad)
{
    (*(m_vertices_iterator + 0)).position = glm::vec2(p_quad.position.x + p_quad.size.x, p_quad.position.y);
    (*(m_vertices_iterator + 1)).position = glm::vec2(p_quad.position.x + p_quad.size.x, p_quad.position.y + p_quad.size.y);
    (*(m_vertices_iterator + 2)).position = glm::vec2(p_quad.position.x, p_quad.position.y + p_quad.size.y);
    (*(m_vertices_iterator + 3)).position = glm::vec2(p_quad.position.x, p_quad.position.y);
    
    (*(m_vertices_iterator + 0)).uv = glm::vec2(p_quad.uv.position.x + p_quad.uv.size.x, p_quad.uv.position.y);
    (*(m_vertices_iterator + 1)).uv = glm::vec2(p_quad.uv.position.x + p_quad.uv.size.x, p_quad.uv.position.y + p_quad.uv.size.y);
    (*(m_vertices_iterator + 2)).uv = glm::vec2(p_quad.uv.position.x, p_quad.uv.position.y + p_quad.uv.size.y);
    (*(m_vertices_iterator + 3)).uv = glm::vec2(p_quad.uv.position.x, p_quad.uv.position.y);
    
    for (auto i { 0 }; i < 4; i++)
    {
        (*(m_vertices_iterator + i)).color.x = p_quad.color.red;
        (*(m_vertices_iterator + i)).color.y = p_quad.color.green;
        (*(m_vertices_iterator + i)).color.z = p_quad.color.blue;
        (*(m_vertices_iterator + i)).color.w = p_quad.color.alpha;
        
        (*(m_vertices_iterator + i)).texture = static_cast<float>(p_quad.texture);
    }
    
    m_vertices_iterator += 4;
    m_quads_to_draw++;
}

void renderer_t::end()
{
    glUseProgram(m_shader_program);
    
    glBindVertexArray(m_vao);
    
    for (auto i { 0 }; i < m_textures.size(); i++)
    {
        if (m_textures[i] != 0)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_textures[i]);
        }
    }
    
    glDrawElements(GL_TRIANGLES, m_quads_to_draw * 6, GL_UNSIGNED_INT, nullptr);
}

renderer_t::~renderer_t()
{
    glUseProgram(0);
    glDeleteProgram(m_shader_program);
    
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_vbo);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_ebo);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    for (auto& texture: m_textures)
    {
        if (texture != 0)
        {
            glDeleteTextures(1, &texture);
        }
    }
}