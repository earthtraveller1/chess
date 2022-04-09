#include <stdexcept>
#include <iostream>

#include <glad/glad.h>

#include "window.hpp"

window_t& window_t::get_instance()
{
    static window_t instance;
    return instance;
}

void window_t::show() const
{
    glfwShowWindow(m_handle);
}

bool window_t::is_open() const
{
    return !glfwWindowShouldClose(m_handle);
}

void window_t::update() const 
{
    glfwSwapBuffers(m_handle);
    glfwPollEvents();
}

window_t::~window_t()
{
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}

window_t::window_t()
{
    if (!glfwInit())
    {
        throw std::runtime_error("failed to initialize glfw.");
    }
    
    glfwSetErrorCallback(
        [] (int p_code, const char* p_message)
        {
            std::cerr << "[GLFW ERROR " << p_code << "]: " << p_message << "\n";
        }
    );
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    
    if (video_mode->height >= 2160)
    {
        m_width = 1920;
        m_height = 1440;
    }
    else if (video_mode->height >= 1440)
    {
        m_width = 1440;
        m_height = 1080;
    }
    else if (video_mode->height >= 1080)
    {
        m_width = 1024;
        m_height = 768;
    }
    else if (video_mode->height < 1080)
    {
        m_width = 800;
        m_height = 600;
    }
    
    m_handle = glfwCreateWindow(m_width, m_height, "Chess", nullptr, nullptr);
    
    if (!m_handle)
    {
        throw std::runtime_error("failed to create the glfw window.");
    }
    
    glfwSetWindowPos(m_handle, (video_mode->width - m_width) / 2, (video_mode->height - m_height) / 2);
    
    glfwMakeContextCurrent(m_handle);
    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error("failed to initialize glad.");
    }
}