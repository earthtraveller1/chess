#ifndef A988A7DA_4730_47DF_9049_4465EC9AC802
#define A988A7DA_4730_47DF_9049_4465EC9AC802

#include <GLFW/glfw3.h>

namespace chess
{
    // A singleton class to create and display a window using GLFW.
    class window_t
    {
    public:
        // Obtain the instance of the class.
        static window_t& get_instance() noexcept;
        
        // Not allowing you to copy windows.
        window_t(window_t&) = delete;
        window_t& operator=(window_t&) = delete;
        
        // Show the window.
        void show() const noexcept;
        
        // Returns whether the window is still open or not.
        bool is_open() const noexcept;
        
        // Update the window.
        void update();
        
        // Destroys the window.
        ~window_t();
    private:
        // Constructor.
        window_t();
        
        // The window handle.
        GLFWwindow* m_window;
        
        // The error callback.
        static void glfw_error_callback(int error_code, const char* error_message);
    };
}

#endif /* A988A7DA_4730_47DF_9049_4465EC9AC802 */
