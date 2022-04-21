#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>

#include <glad/glad.h>

#ifdef _WIN32
    #include <Windows.h>
#endif

#include "window.hpp"
#include "board.hpp"
#include "renderer.hpp"
#include "pieces.hpp"

namespace
{

void debug_break()
{
    
}

class application_t
{
public:
    application_t(bool p_enable_context_debugging): m_window(window_t::get_instance(p_enable_context_debugging)), m_rectangle_angle { 0.0f }
    {
        if (p_enable_context_debugging)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

            glDebugMessageCallback(
                [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) -> void
                {
                    std::cout << "[OPENGL]: " << message << std::endl;
                    debug_break();
                },
                nullptr);
        }
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        board::init();
        renderer::init();
        pieces::init();
        
        m_window.show();
    }
    
    bool is_running()
    {
        return m_window.is_open();
    }
    
    void update()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        board::render();
        
        renderer::begin();
        
        for (auto i = static_cast<uint8_t>(0); i < 8; i++)
        {
            pieces::draw_pieces();
        }
        
        renderer::end();
        
        /*renderer::begin();
        renderer::draw_rotated_colored_rectangle(15.0f, 20.0f, 10.0f, 10.0f, m_rectangle_angle, 1.0f, 0.0f, 0.0f, 1.0f);
        renderer::end();*/
        
        m_rectangle_angle += 1.0f;
        
        m_window.update();
    }
    
    ~application_t()
    {
        board::cleanup();
        renderer::cleanup();
    }
    
private:
    window_t& m_window;
    float m_rectangle_angle;
};

static void run(bool p_enable_context_debug)
{
    application_t application(p_enable_context_debug);
    
    while (application.is_running())
    {
        application.update();
    }
}

static void display_fatal_error(const char* p_error_message)
{
    #ifdef _WIN32
        size_t error_message_size = std::strlen(p_error_message);
        wchar_t* error_message = new wchar_t[error_message_size];
        mbstowcs_s(&error_message_size, error_message, error_message_size * 2, p_error_message, error_message_size - 1);
        
        MessageBoxW(nullptr, error_message, L"FATAL ERROR", MB_OK | MB_ICONERROR);
        
        delete[] error_message;
    #else 
        std::cerr << "[FATAL ERROR]: " << p_error_message << "\n";
    #endif
}

static std::vector<std::wstring> split_string(std::wstring_view p_master_string)
{
    std::vector<std::wstring> result;
    
    std::wstringstream master_string(p_master_string.data());
    
    std::wstring token;
    while (std::getline(master_string, token, L' '))
    {
        result.push_back(token);
    }
    
    return result;
}
}

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE p_h_instance, HINSTANCE, PWSTR p_command_line, int p_show)
{
    auto enable_context_debug = false;
    
    auto command_line_arguments = split_string(p_command_line);
    
    for (const auto& argument: command_line_arguments)
    {
        if (argument == L"--enable-context-debugging")
        {
            enable_context_debug = true;
        }
    }
    
    try
    {
        run(enable_context_debug);
    }
    catch (const std::runtime_error& e)
    {
        auto error_message_ascii = e.what();
        auto size = std::strlen(error_message_ascii);
        auto error_message = new wchar_t[size];
        auto bytes_converted { static_cast<size_t>(0) };
        mbstowcs_s(&bytes_converted, error_message, size, error_message_ascii, size);
        
        MessageBoxW(nullptr, error_message, L"FATAL ERROR", MB_OK | MB_ICONERROR);
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
#endif

int main(int argc, char** argv)
{
    bool enable_context_debug = false;
    
    for (int32_t i = 0; i < argc; i++)
    {
        if (std::strcmp(argv[i], "--enable-context-debugging") == 0)
        {
            enable_context_debug = true;
            std::cout << "[INFO]: Enabling context debugging (requires OpenGL 4.3)\n";
        }
    }
    
    try
    {
        run(enable_context_debug);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "[FATAL ERROR]: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
