#include "application.hpp"
#include <stdexcept>
#include <iostream>
#include <cstdlib>

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