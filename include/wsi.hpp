#pragma once

#include <GLFW/glfw3.h>


// Window System Integration

typedef void (*proc_addr)();

inline void init_wsi()
{
    glfwInit();
}
inline void terminate_wsi()
{
	glfwTerminate();
}

inline proc_addr get_proc_addr()
{
	return (proc_addr)(&glfwGetProcAddress);
}


// Window creation

inline GLFWwindow* create_window()
{
	// OpenGL core 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(1366, 768, "OpenGL Tutorial", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	return window;
}
inline void destroy_window(GLFWwindow* window)
{
	glfwDestroyWindow(window);
}
