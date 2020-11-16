#include "rect.hpp"

Rect::Rect(float x, float y, float width, float height) {
    float testVert[32] = {
        // positions          // colors           // texture coords
        x +  width, y +  height, 0.0f,   1.0f, 0.0f, 0.0f,   -1.0f, 1.0f, // top right
        x +  width, y + -height, 0.0f,   0.0f, 1.0f, 0.0f,   -1.0f, 0.0f, // bottom right
        x + -width, y + -height, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        x + -width, y +  height, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    for(int i = 0; i < 32; i++) {
        vertices[i] = testVert[i];
    }

    unsigned int testIndi[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    for(int j = 0; j < 6; j++) {
        indices[j] = testIndi[j];
    }
}