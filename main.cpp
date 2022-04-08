#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit())
    {
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Chess", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
        return -2;
    }
    
    glfwMakeContextCurrent(window);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}