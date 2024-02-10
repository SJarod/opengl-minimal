#pragma once

#include <iostream>

#include <glad/gl.h>
#include "wsi.hpp"


// OpenGL

inline void opengl_load_symbols()
{
	if (!gladLoadGL((GLADloadfunc)get_proc_addr()))
		throw std::exception("Failed to load OpenGL functions");
}

inline void opengl_create_vertex_buffer(GLuint& handle,
	const float* vertices,
	const unsigned int& vertexCount)
{
	glGenBuffers(1, &handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
inline void opengl_create_vertex_array(GLuint& handle, const GLuint& vbo)
{
	glGenVertexArrays(1, &handle);
	glBindVertexArray(handle);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // strides
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

// shader program handle
inline void opengl_compile_shaders(GLuint& spHandle, const char* vsSource, const char* fsSource)
{
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
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

	spHandle = glCreateProgram();
	glAttachShader(spHandle, vs);
	glAttachShader(spHandle, fs);
	glLinkProgram(spHandle);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

// shader program handle
inline void draw_frame(const GLuint& spHandle, const GLuint& vao)
{
	glViewport(0, 0, 1366, 768);

	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(spHandle);
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}
