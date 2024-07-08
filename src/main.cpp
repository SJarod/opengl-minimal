#include "opengl_tutorial.hpp"


// TODO : remove glad and load opengl functions from dll


float vertices[] = {
	// x, y, z, r, g, b
	0.f, 0.5f, 0.f, 1.f, 0.f, 0.f,
	0.5f, -0.5f, 0.f, 0.f, 1.f, 0.f,
	-0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f
};

const char* vstriangleSrc = R"GLSL(
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 oFrag;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	oFrag = aColor;
}
)GLSL";

const char* fstriangleSrc = R"GLSL(
#version 450 core

in vec3 oFrag;

out vec4 oColor;

void main()
{
	oColor = vec4(oFrag, 1.0);
}
)GLSL";


int main()
{
	// TODO : ubo (mvp)
	// TODO : texture

	GLuint vbo;
	GLuint vao;
	GLuint shaderProgram;
	
	try
	{
		init_wsi();

		GLFWwindow* window = create_window();

		opengl_load_symbols();

		opengl_create_vertex_buffer(vbo, vertices, sizeof(vertices));
		opengl_create_vertex_array(vao, vbo);
		opengl_compile_shaders(shaderProgram, vstriangleSrc, fstriangleSrc);

		while (!glfwWindowShouldClose(window))
		{
			glfwSwapBuffers(window);
			glfwPollEvents();

			draw_frame(shaderProgram, vao);
		}

		destroy_window(window);

		terminate_wsi();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
