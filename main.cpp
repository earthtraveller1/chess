#include <stdexcept>
#include <iostream>
#include <cstdlib>

#include "application.hpp"
#include "utilities.hpp"
#include "option-loader.hpp"

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
            
            while (application.is_open())
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
        
        return EXIT_SUCCESS;
    }
}

#if 0
int main()
{
    chess::option_loader_t options { "options.txt" };
    
    std::cout << "This thing is set to: " << options.get_option_value("flip_board_on_move") << "\n";
    
    return 0;
}
#endif

//#if 0
int main()
{
    std::cout << "[INFO]: Hello!\n";
    return run();
}
//#endif

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE p_instance, HINSTANCE, LPWSTR p_command_line_arguments, int p_show_command)
{
    UNUSED_PARAM(p_instance);
    UNUSED_PARAM(p_command_line_arguments);
    UNUSED_PARAM(p_show_command);
    
    return run();
}
#endif