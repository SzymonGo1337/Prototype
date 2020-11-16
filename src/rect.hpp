#pragma once

#include <glad/glad.h>
#include <iostream>

class Rect {
public:
    float vertices[32];
    unsigned int indices[6];

    Rect(float x, float y, float width, float height);
    void transform(float x, float y, float width, float height);
};