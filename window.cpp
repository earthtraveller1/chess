#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>

#include "application.hpp"
#include "utilities.hpp"

#include "window.hpp"

using chess::window_t;

window_t& window_t::get_instance() noexcept
{
    static window_t instance;
    return instance;
}

void window_t::set_mouse_button_event_handler(GLFWmousebuttonfun p_handler)
{
    glfwSetMouseButtonCallback(m_window, p_handler);
}

void window_t::set_mouse_position_event_handler(GLFWcursorposfun p_handler)
{
    glfwSetCursorPosCallback(m_window, p_handler);
}

void window_t::show() const noexcept
{
    glfwShowWindow(m_window);
}

bool window_t::is_open() const noexcept
{
    return !glfwWindowShouldClose(m_window);
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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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
    
    std::array<std::array<uint32_t, 24>, 24> icon_pixels;
    
    for (auto& icon_pixel_row: icon_pixels)
    {
        for (auto i { static_cast<uint8_t>(0) }; i < 8; i++)
        {
            icon_pixel_row[i] = 0xffff0000;
        }
        
        for (auto i { static_cast<uint8_t>(8) }; i < 16; i++)
        {
            icon_pixel_row[i] = 0xffffffff;
        }
        
        for (auto i { static_cast<uint8_t>(16) }; i < 24; i++)
        {
            icon_pixel_row[i] = 0xff0000ff;
        }
    }
    
    GLFWimage icon;
    icon.height = 24;
    icon.width = 24;
    icon.pixels = reinterpret_cast<unsigned char*>(icon_pixels.data());
    
    glfwSetWindowIcon(m_window, 1, &icon);
    
    glfwMakeContextCurrent(m_window);
    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error("Failed to load OpenGL ICD.");
    }
}

void window_t::glfw_error_callback(int p_error_code, const char* p_error_message) noexcept
{
    std::cerr << "[GLFW ERROR " << p_error_code << "]: " << p_error_message << std::endl;
}