#pragma once
#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"

class Texture {
public:
    Texture(const char* filename);

    void Bind();
    void Unbind();

private:
    unsigned int texture;
    int width, height, nrChannels;
    unsigned char *data;
};