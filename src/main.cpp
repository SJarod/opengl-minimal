#include <vector>

#include "vertex.hpp"

#include "opengl_minimal.hpp"

#include "triangle.frag.hpp"
#include "triangle.vert.hpp"

// TODO : remove glad and load opengl functions from dll

int main()
{
    // TODO : ubo (mvp)
    // TODO : texture

    WSI::init();

    int width = 1366, height = 768;

    GLFWwindow *window = WSI::create_window(width, height, "OpenGL Minimal");

    RHI::load_symbols();

    const std::vector<Vertex> vertices = {{{-0.5f, -0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, {1.f, 0.f}},
                                          {{0.5f, -0.5f, 0.f}, {0.f, 1.f, 0.f, 1.f}, {0.f, 0.f}},
                                          {{0.5f, 0.5f, 0.f}, {0.f, 0.f, 1.f, 1.f}, {0.f, 1.f}},
                                          {{-0.5f, 0.5f, 0.f}, {1.f, 1.f, 1.f, 1.f}, {1.f, 1.f}},
                                          {{-0.5f, -0.5f, -0.5f}, {1.f, 0.f, 0.f, 1.f}, {1.f, 0.f}},
                                          {{0.5f, -0.5f, -0.5f}, {0.f, 1.f, 0.f, 1.f}, {0.f, 0.f}},
                                          {{0.5f, 0.5f, -0.5f}, {0.f, 0.f, 1.f, 1.f}, {0.f, 1.f}},
                                          {{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {1.f, 1.f}}};
    GLuint vbo = RHI::Memory::Buffer::create_vertex_buffer(vertices);
    GLuint vao = RHI::Memory::Buffer::create_vertex_array(vbo);
    GLuint program = RHI::Shader::create_shader_program(triangleVertSrc, triangleFragSrc);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        glViewport(0, 0, width, height);

        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
    }

    WSI::destroy_window(window);

    WSI::terminate();

    return EXIT_SUCCESS;
}
