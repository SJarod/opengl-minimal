#pragma once

const char *triangleFragSrc = R"GLSL(
    #version 450 core
    
    in vec3 oFrag;
    
    out vec4 oColor;
    
    void main()
    {
        oColor = vec4(oFrag, 1.0);
    }
    )GLSL";