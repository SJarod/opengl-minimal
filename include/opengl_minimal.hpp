#pragma once

#include <iostream>

#include <glad/gl.h>
#include "wsi.hpp"

namespace RHI
{

inline void load_symbols()
{
    if (!gladLoadGL((GLADloadfunc)WSI::get_proc_addr()))
        std::cerr << "Failed to load OpenGL functions" << std::endl;
}

namespace Memory
{
inline void create_vertex_buffer(GLuint &handle, const float *vertices, const unsigned int &vertexCount)
{
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
inline void create_vertex_array(GLuint &handle, const GLuint &vbo)
{
    glGenVertexArrays(1, &handle);
    glBindVertexArray(handle);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // strides
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
} // namespace Memory

namespace Shader
{
inline void compile_shaders(GLuint &spHandle, const char *vsSource, const char *fsSource)
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

        std::cerr << "Failed to compile shaders" << std::endl;
    }

    spHandle = glCreateProgram();
    glAttachShader(spHandle, vs);
    glAttachShader(spHandle, fs);
    glLinkProgram(spHandle);

    glDeleteShader(vs);
    glDeleteShader(fs);
}
} // namespace Shader
} // namespace RHI