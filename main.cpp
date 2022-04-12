#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include <glad/glad.h>

#ifdef _WIN32
    #include <Windows.h>
#endif

#include "window.hpp"
#include "board.hpp"

class application_t
{
public:
    application_t(bool p_enable_context_debugging): m_window(window_t::get_instance(p_enable_context_debugging))
    {
        if (p_enable_context_debugging)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

            glDebugMessageCallback(
                [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) -> void
                {
                    std::cout << "[OPENGL]: " << message << std::endl;
                },
                nullptr);
        }
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
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
        
        m_window.update();
    }
    
    ~application_t()
    {
        
    }
    
private:
    window_t& m_window;
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