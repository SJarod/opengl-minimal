#pragma once

const char *triangleFragSrc = R"GLSL(
    #version 450 core
    
    in vec3 fragColor;
    in vec2 fragUV;
    
    out vec4 oColor;

    uniform sampler2D texSampler;
    
    void main()
    {
        oColor = texture(texSampler, fragUV);
    }
    )GLSL";