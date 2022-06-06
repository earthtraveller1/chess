#include <glad/glad.h>
#include <iostream>

#include "window.hpp"
#include "utilities.hpp"

#include "application.hpp"

using chess::application_t;

namespace 
{
    chess::piece_manager_t* piece_manager { nullptr };
    
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        UNUSED_PARAM(window);
        UNUSED_PARAM(mods);
        
        if (piece_manager != nullptr)
        {
            if (button == GLFW_MOUSE_BUTTON_LEFT)
            {
                if (action == GLFW_PRESS)
                {
                    piece_manager->set_dragging(true);
                }
                else if (action == GLFW_RELEASE)
                {
                    piece_manager->set_dragging(false);
                }
            }
        }
    }
    
    void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
    {
        auto window_width { 0 };
        auto window_height { 0 };
        
        glfwGetWindowSize(window, &window_width, &window_height);
        
        auto normalized_x { (xpos / window_height) * 8.0 };
        auto normalized_y { (ypos / window_height) * 8.0 };
        
        piece_manager->update_mouse_position(normalized_x, normalized_y);
    }
}

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
    piece_manager = &m_piece_manager;
    board = &m_board;
    
    m_window.set_mouse_button_event_handler(mouse_button_callback);
    m_window.set_mouse_position_event_handler(cursor_pos_callback);
    
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