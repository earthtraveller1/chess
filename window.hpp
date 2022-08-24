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
    static window_t &get_instance() noexcept;

    // Not allowing you to copy windows.
    window_t(window_t &) = delete;
    window_t &operator=(window_t &) = delete;

    // Set the mouse button event handler
    void set_mouse_button_event_handler(GLFWmousebuttonfun event_handler);

    // Set the mouse position event handler
    void set_mouse_position_event_handler(GLFWcursorposfun event_handler);

    // Set the key event handler
    inline void set_key_event_handler(GLFWkeyfun event_handler)
    {
        glfwSetKeyCallback(m_window, event_handler);
    }

    // Set the user pointer of the window
    template <typename T> void set_user_pointer(T *p_user_pointer)
    {
        glfwSetWindowUserPointer(m_window, p_user_pointer);
    }

    // Getters for the window sizes
    uint16_t get_width() const;
    uint16_t get_height() const;

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
    GLFWwindow *m_window;

    // The error callback.
    static void glfw_error_callback(int error_code,
                                    const char *error_message) noexcept;
};
} // namespace chess

#endif /* A988A7DA_4730_47DF_9049_4465EC9AC802 */
