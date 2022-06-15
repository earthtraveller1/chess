#include <sstream>

#include "utilities.hpp"

#include "option-loader.hpp"

using chess::option_loader_t;

namespace 
{
    struct option_t
    {
        std::string name;
        std::string value;
    };
    
    option_t process_option(std::string_view p_line)
    {
        std::string name;
        
        for (auto character: p_line)
        {
            
        }
    }
}

option_loader_t::option_loader_t(std::string_view p_file)
{
    // Load the file first.
    auto raw { utilities::load_as_string(p_file) };
    
    // Use default options if the option file doesn't exist.
    if (raw == "")
    {
        m_options.at("flip_board_on_move") = "false";
        return;
    }
    
    std::stringstream stream(raw);
    
    while (!stream.eof())
    {
        
    }
}