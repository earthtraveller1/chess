#ifndef E7285229_48B6_455A_A806_FA24E7743CB1
#define E7285229_48B6_455A_A806_FA24E7743CB1

#include <GLFW/glfw3.h>

class window_t
{
public:
    window_t(window_t&) = delete;
    window_t& operator=(window_t&) = delete;
    
    static window_t& get_instance();
    
    void show() const;
    
    bool is_open() const;
    
    void update() const;
    
    ~window_t();
    
private:
    window_t();
    
    GLFWwindow* m_handle;
    
    uint32_t m_width;
    uint32_t m_height;
};

#endif /* E7285229_48B6_455A_A806_FA24E7743CB1 */
