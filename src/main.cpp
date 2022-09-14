#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

void windowInit();
void openglInit();

GLFWwindow* window;

const char* vstriangleSrc = R"GLSL(
#version 450

out vec3 vertexColor;

vec2 positions[3] = {
	vec2(0.0, -0.5),
	vec2(0.5, 0.5),
	vec2(-0.5, 0.5)
};

vec3 colors[3] = {
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, 1.0, 0.0),
	vec3(0.0, 0.0, 1.0)
};

void main()
{
	gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
	vertexColor = colors[gl_VertexIndex];
}
)GLSL";

const char* fstriangleSrc = R"GLSL(
#version 450

in vec3 vertexColor;

layout(location = 0) out vec4 oColor;

void main()
{
	oColor = vec4(vertexColor, 1.0);
}
)GLSL";

void windowInit()
{
	// OpenGL core 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(800, 600, "OpenGL window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
}

void openglInit()
{
	if (!gladLoadGL(glfwGetProcAddress))
		throw std::exception("Failed to load OpenGL functions");
}

int main()
{
	try
	{
		glfwInit();

		windowInit();
		openglInit();

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return EXIT_SUCCESS;
}