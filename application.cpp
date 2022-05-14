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

application_t::application_t(): m_window(window_t::get_instance())
{
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
    
    m_piece_manager.render_pieces();
    
    m_window.update();
}

bool application_t::is_open() const
{
    return m_window.is_open();
}

application_t::~application_t()
{
    
}