#include <sstream>

#include "utilities.hpp"

#include "option-loader.hpp"

using chess::option_loader_t;
using namespace std::string_literals;

namespace
{
struct option_t
{
    std::string name;
    std::string value;
};

option_t process_option(std::string_view p_line)
{
    auto name{""s};

    for (auto character : p_line)
    {
        if (character == '=')
        {
            break;
        }
        else
        {
            name += character;
        }
    }

    auto value{""s};

    for (auto i{p_line.find_first_of("=") + 1}; i < p_line.size(); i++)
    {
        value += p_line[i];
    }

    return {name, value};
}
} // namespace

option_loader_t::option_loader_t(std::string_view p_file)
{
    // Load the file first.
    auto raw{utilities::load_as_string(p_file)};

    // Use default options if the option file doesn't exist.
    if (raw == "")
    {
        m_options["flip_board_on_move"] = "false";
        return;
    }

    std::stringstream stream(raw);

    while (!stream.eof())
    {
        auto line{""s};
        std::getline(stream, line);

        auto option{process_option(line)};

        m_options[option.name] = option.value;
    }
}