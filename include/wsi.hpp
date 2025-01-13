#pragma once

#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

// Window System Integration
namespace WSI
{
typedef void (*proc_addr)();

inline void init()
{
    glfwInit();
}
inline void terminate()
{
    glfwTerminate();
}

inline proc_addr get_proc_addr()
{
    return (proc_addr)(&glfwGetProcAddress);
}

// Window creation

inline GLFWwindow *create_window(int width, int height, const char *windowName)
{
    // OpenGL core 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    return window;
}
inline void destroy_window(GLFWwindow *window)
{
    glfwDestroyWindow(window);
}

inline const std::vector<const char *> get_required_extensions()
{
    uint32_t count = 0;
    const char **extensions;

    extensions = glfwGetRequiredInstanceExtensions(&count);

    return std::vector<const char *>(extensions, extensions + count);
}

inline void make_context_current(GLFWwindow *window)
{
    glfwMakeContextCurrent(window);
}

inline void swap_buffers(GLFWwindow *window)
{
    glfwSwapBuffers(window);
}
inline void poll_events()
{
    glfwPollEvents();
}

inline bool should_close(GLFWwindow *window)
{
    return glfwWindowShouldClose(window);
}

} // namespace WSI
