#ifndef AD37DA30_D0E5_4ABB_8835_9A59E058148C
#define AD37DA30_D0E5_4ABB_8835_9A59E058148C

#include <string>
#include <string_view>

// A set of useful utilities that I might use a lot.

// Define a function parameter as unused.
#define UNUSED_PARAM(x) (void)x

namespace chess
{
namespace utilities
{
// Load a text file from disk and return it's contents into an std::string
std::string load_as_string(std::string_view path);

// Create a shader object of a specific type and return it's ID.
uint32_t create_shader(std::string_view source, uint32_t type) noexcept;

// Create a shader program and return it's ID.
uint32_t create_shader_program(uint32_t vertex, uint32_t fragment);
} // namespace utilities
} // namespace chess

#endif /* AD37DA30_D0E5_4ABB_8835_9A59E058148C */
