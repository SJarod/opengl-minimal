#include "opengl_minimal.hpp"

// TODO : remove glad and load opengl functions from dll

float vertices[] = {
    // x, y, z, r, g, b
    0.f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f, -0.5f, 0.f, 0.f, 1.f, 0.f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f};

const char *vstriangleSrc = R"GLSL(
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

const char *fstriangleSrc = R"GLSL(
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

    WSI::init();

    int width = 1366, height = 768;

    GLFWwindow *window = WSI::create_window(width, height, "OpenGL Minimal");

    RHI::load_symbols();

    RHI::Memory::create_vertex_buffer(vbo, vertices, sizeof(vertices));
    RHI::Memory::create_vertex_array(vao, vbo);
    RHI::Shader::compile_shaders(shaderProgram, vstriangleSrc, fstriangleSrc);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        glViewport(0, 0, width, height);

        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
    }

    WSI::destroy_window(window);

    WSI::terminate();

    return EXIT_SUCCESS;
}
