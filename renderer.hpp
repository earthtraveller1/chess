#ifndef A981AA12_73E4_4023_A7E9_9EB3EEBE93E7
#define A981AA12_73E4_4023_A7E9_9EB3EEBE93E7

#include <cstdint>
#include <string_view>
#include <array>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace chess
{
    // A simple 2D renderer that can render 2D textured quads.
    class renderer_t
    {
    public:
        renderer_t(uint32_t max_quads, std::string_view vertex_shader, std::string_view fragment_shader);
        
        // Disable copying.
        renderer_t(renderer_t&) = delete;
        renderer_t& operator=(renderer_t&) = delete;
        
        // Add a texture.
        void set_texture(std::string_view path, uint8_t slot) noexcept;
        
        // Start drawing
        void begin();
        
        // Struct representing information about a quad.
        struct quad_t
        {
            struct 
            {
                float x;
                float y;
            } position;
            
            struct 
            {
                float x;
                float y;
            } size;
            
            struct 
            {
                struct 
                {
                    float x;
                    float y;
                } position;
                
                struct 
                {
                    float x;
                    float y;
                } size;
            } uv;
            
            struct 
            {
                float red;
                float green;
                float blue;
                float alpha;
            } color;
            
            int8_t texture;
        };
        
        // Draw a quad.
        void draw_quad(const quad_t& quad);
        
        // Stop drawing
        void end();
        
        // Cleans up resources.
        ~renderer_t();
        
    private:
        // No one else uses the vertex struct, so it's private.
        struct vertex_t
        {
            glm::vec2 position;
            glm::vec2 uv;
            glm::vec4 color;
            float texture;
        };
        
        // OpenGL resources
        uint32_t m_vao;
        uint32_t m_vbo;
        uint32_t m_ebo;
        
        // Maximum number of quads.
        uint32_t m_max_number_of_quads;
        
        // The number of quads to draw.
        uint32_t m_quads_to_draw { 0 };
        
        // CPU-side buffers
        std::vector<vertex_t> m_vertices;
        
        // Iterators for CPU side buffers.
        std::vector<vertex_t>::iterator m_vertices_iterator;
        
        // Shader
        uint32_t m_shader_program;
        
        // Textures
        std::array<uint32_t, 32> m_textures;
    };
}

#endif /* A981AA12_73E4_4023_A7E9_9EB3EEBE93E7 */
