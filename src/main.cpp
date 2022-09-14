#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

void windowInit();
void openglInit();
void openglCompileShaders();

GLFWwindow* window;
GLuint shaderProgram;

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
	gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
	vertexColor = colors[gl_VertexID];
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

void openglCompileShaders()
{
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vstriangleSrc, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fstriangleSrc, NULL);
	glCompileShader(fs);

	int success[2];
	char infoLog[2][512];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success[0]);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success[1]);

	if (!success[0] || !success[1])
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog[0]);
		std::cout << infoLog[0] << std::endl;
		glGetShaderInfoLog(fs, 512, NULL, infoLog[1]);
		std::cout << infoLog[1] << std::endl;

		throw std::exception("Failed to compile shaders");
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

int main()
{
	try
	{
		glfwInit();

		windowInit();
		openglInit();
		openglCompileShaders();

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