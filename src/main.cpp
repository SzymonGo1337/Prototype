#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <Windows.h>

#include "shader.hpp"
#include "texture.hpp"
#include "rect.hpp"

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        glfwHideWindow(window);
        Sleep(2000);
        glfwShowWindow(window);
    }

    if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        glfwSetWindowOpacity(window, 0.0f);
        Sleep(2000);
        glfwSetWindowOpacity(window, 1.0f);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void glfwSetup() {
	if(!glfwInit()) {
		std::cerr << "GLFW Init Error" << "\n";
		exit(EXIT_FAILURE);
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
    	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330\n"
					             "layout(location = 0) in vec3 aPos;\n"
					             "layout(location = 1) in vec3 aColor;\n"
                                 "layout(location = 2) in vec2 aTexCoord;\n"
					             "out vec3 ourColor;\n"
                                 "out vec2 TexCoord;\n"
					             "void main() {\n"
					             	 "gl_Position = vec4(aPos, 1.0);\n"
                                     "ourColor = aColor;\n"
                                     "TexCoord = aTexCoord;\n"
					             "}";

const char *fragmentShaderSource =	"#version 330\n"
	                                "out vec4 FragColor;\n"
                                    "in vec3 ourColor;\n"
	                                "in vec2 TexCoord;\n"
                                    "uniform sampler2D ourTexture;\n"
	                                "void main() {\n"
	                                	"FragColor = texture(ourTexture, TexCoord);\n"
	                                "}";

int main(int argv, char** argc) {
    glfwSetup();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Prototype", NULL, NULL);
    if(window == NULL) {
        std::cerr << "Failed to create GLFW window" << "\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << "\n";
        exit(EXIT_FAILURE);
    }

	Shader shader(vertexShaderSource, fragmentShaderSource);

    Rect rect(0.5f, 0.5f, 0.25f, 0.25f);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect.vertices), rect.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect.indices), rect.indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Texture texture("test.jpg");

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render
		texture.Bind();

        shader.Bind();
		glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.Unbind();
    texture.Unbind();

    glfwTerminate();
    return 0;
}