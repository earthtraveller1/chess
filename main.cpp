#include "application.hpp"
#include <stdexcept>
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace 
{
    int run()
    {
        try
        {
            chess::application_t application;
            
            while (true)
            {
                application.update(0);
                application.render();
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "[FATAL ERROR]: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        catch (const chess::exit_exception_t& e)
        {
            return EXIT_SUCCESS;
        }
    }
}

int main()
{
    return run();
}

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE p_instance, HINSTANCE, LPWSTR p_command_line_arguments, int p_show_command)
{
    return run();
}
#endif