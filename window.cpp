#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "application.hpp"
#include "utilities.hpp"

#include "window.hpp"

using chess::window_t;

window_t& window_t::get_instance()
{
    static window_t instance;
    return instance;
}

void window_t::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

window_t::~window_t()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

window_t::window_t()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW.");
    }
    
    glfwSetErrorCallback(glfw_error_callback);
    
    #ifdef NDEBUG
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
    #else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    #endif
    
    #ifdef APPLE
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    #endif
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    
    auto video_mode { glfwGetVideoMode(glfwGetPrimaryMonitor()) };
    
    auto window_size { static_cast<uint16_t>(0) };
    
    if (video_mode->height >= 2160)
    {
        window_size = 1600;
    }
    else if (video_mode->height >= 1440)
    {
        window_size = 1000;
    }
    else if (video_mode->height >= 1080)
    {
        window_size = 800;
    }
    else if (video_mode->height < 1080)
    {
        window_size = 600;
    }
    
    m_window = glfwCreateWindow(window_size, window_size, "Chess", nullptr, nullptr);
    
    if (m_window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window.");
    }
    
    glfwSetWindowPos(m_window, (video_mode->width - window_size) / 2, (video_mode->height - window_size) / 2);
    
    glfwMakeContextCurrent(m_window);
    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error("Failed to load OpenGL ICD.");
    }
    
    glfwSetWindowCloseCallback(m_window, glfw_close_callback);
}

void window_t::glfw_error_callback(int p_error_code, const char* p_error_message)
{
    std::cerr << "[GLFW ERROR " << p_error_code << "]: " << p_error_message << std::endl;
}

void window_t::glfw_close_callback(GLFWwindow* p_window)
{
    UNUSED_PARAM(p_window);
    throw exit_exception_t {};
}