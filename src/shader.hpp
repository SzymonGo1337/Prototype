#pragma once
#include <glad/glad.h>
#include <iostream>

class Shader {
public:
    Shader(const char *vert, const char *frag);

    void Bind();
    void Unbind();

private:
    int program;
};
