#ifndef E70FAB5C_4A67_4ABA_9EA4_BA9C2E8B2435
#define E70FAB5C_4A67_4ABA_9EA4_BA9C2E8B2435

#include <string>
#include <string_view>
#include <unordered_map>

namespace chess
{
// A simple utility class to load options. I used maps instead of just mem-
// ber variables because that makes it more extensible.
class option_loader_t
{
  public:
    option_loader_t(std::string_view file = "options.txt");

    inline std::string get_option_value(std::string_view name)
    {
        return m_options.at(name.data());
    }

  private:
    // The entire map containing names to values.
    std::unordered_map<std::string, std::string> m_options;
};
} // namespace chess

#endif /* E70FAB5C_4A67_4ABA_9EA4_BA9C2E8B2435 */
