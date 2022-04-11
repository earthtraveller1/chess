#ifndef BAF57771_1B00_4D93_94F7_CB9F5C354026
#define BAF57771_1B00_4D93_94F7_CB9F5C354026

#include <cstdint>
#include <string_view>

namespace shaders
{
    uint32_t create_shader(std::string_view p_path, uint32_t p_type);
    
    uint32_t create_shader_program(uint32_t p_vertex, uint32_t p_fragment);
}

#endif /* BAF57771_1B00_4D93_94F7_CB9F5C354026 */
