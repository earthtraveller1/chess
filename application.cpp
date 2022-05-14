#include <glad/glad.h>
#include <iostream>

#include "window.hpp"
#include "utilities.hpp"

#include "application.hpp"

using chess::application_t;

application_t::context_debugger::context_debugger()
{
    #ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    
    glDebugMessageCallback([] (GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar *p_message,const void*) {
        std::clog << "[OPENGL]: " << p_message;
        std::clog << std::endl;
    }, nullptr);
    
    std::cout << "[INFO]: Enabled OpenGL context debugging.\n";
    #endif
    
    // Technically, this does not go here, but okay.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

application_t::application_t(): m_window(window_t::get_instance()), m_renderer(2, "renderer-shader.vert", "renderer-shader.frag")
{
    m_renderer.set_texture("test-texture.png", 0);
    
    m_window.show();
}

void application_t::update(double p_delta_time)
{
    UNUSED_PARAM(p_delta_time);
}

void application_t::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    m_board.render();
    
    m_renderer.begin();
    
    renderer_t::quad_t quad = {};
    quad.position.x = 2.0f;
    quad.position.y = 1.0f;
    quad.size.x = 3.0f;
    quad.size.y = 3.0f;
    quad.color = { 0.1f, 0.16f, 0.67f, 1.0f };
    quad.texture = -1;
    
    m_renderer.draw_quad(quad);
    
    renderer_t::quad_t quad_2 = {};
    quad_2.position.x = 3.0f;
    quad_2.position.y = 5.0f;
    quad_2.size.x = 2.0f;
    quad_2.size.y = 2.0f;
    quad_2.uv.position.x = 0.0f;
    quad_2.uv.position.y = 0.0f;
    quad_2.uv.size.x = 1.0f;
    quad_2.uv.size.y = 1.0f;
    quad_2.color = { 1.0f, 1.0f, 1.0f, 1.0f };
    quad_2.texture = 0;
    
    m_renderer.draw_quad(quad_2);
    
    m_renderer.end();
    
    m_window.update();
}

bool application_t::is_open() const
{
    return m_window.is_open();
}

application_t::~application_t()
{
    
}