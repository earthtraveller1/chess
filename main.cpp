#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>

#ifdef _WIN32
    #include <Windows.h>
#endif

#include "window.hpp"

class application_t
{
public:
    application_t(): m_window(window_t::get_instance())
    {
        m_window.show();
    }
    
    bool is_running()
    {
        return m_window.is_open();
    }
    
    void update()
    {
        m_window.update();
    }
    
    ~application_t()
    {
        
    }
    
private:
    window_t& m_window;
};

static void run()
{
    application_t application;
    
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

int main()
{
    try
    {
        run();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "[FATAL ERROR]: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}