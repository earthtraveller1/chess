#include <stdexcept>
#include <iostream>

#include <glad/glad.h>

#include "window.hpp"

window_t& window_t::get_instance(bool p_enable_context_debugging)
{
    static window_t instance(p_enable_context_debugging);
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

window_t::window_t(bool p_enable_context_debugging)
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
    
    if (p_enable_context_debugging)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    }
    else 
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    }
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
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