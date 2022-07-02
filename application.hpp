#ifndef BB8F30B8_A881_40E4_B62B_1F740D539CD1
#define BB8F30B8_A881_40E4_B62B_1F740D539CD1

#include <GLFW/glfw3.h>

#include "scene-manager.hpp"

namespace chess
{
    class window_t;
    
    // Thrown when the game exits.
    struct exit_exception_t {};
    
    // A basic application class to encapsulate most 
    class application_t
    {
    public:
        application_t();
        
        // Prevent copying
        application_t(application_t&) = delete;
        application_t& operator=(application_t&) = delete;
        
        void update(double delta_time);
        
        void render();
        
        inline static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
        {
            reinterpret_cast<application_t*>(glfwGetWindowUserPointer(window))->m_scene_manager.active_on_mouse_click(button, action);
        }
        
        inline static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
        {
            reinterpret_cast<application_t*>(glfwGetWindowUserPointer(window))->m_scene_manager.active_on_mouse_move(xpos, ypos);
        }
        
        bool is_open() const;
        
        ~application_t();
        
    private:
        window_t& m_window;
        
        struct context_debugger
        {
            context_debugger();
        } m_context_debugger;
        
        scene_manager_t m_scene_manager;
    };
}

#endif /* BB8F30B8_A881_40E4_B62B_1F740D539CD1 */
