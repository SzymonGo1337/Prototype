#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <Windows.h>
#include "stb_image.h"

#include "shader.hpp"

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        glfwHideWindow(window);
        Sleep(2000);
        glfwShowWindow(window);
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
    	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330\n"
					"layout(location = 0) in vec3 a_Pos;\n"
					"layout(location = 1) in vec2 a_TexCoord;\n"
					"out vec2 v_TexCoord;\n"
					"uniform mat4 u_ViewProjection = mat4(1.0);\n"
					"uniform mat4 u_Transform = mat4(1.0);\n"
					"void main() {\n"
						"v_TexCoord = a_Pos.xy;\n"
						"gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0);\n"
					"}";

const char *fragmentShaderSource =	"#version 330\n"
					"uniform vec4 u_Color = vec4(1.0, 1.0, 1.0, 1.0);\n"
					"uniform sampler2D u_Texture;\n"
					"out vec4 Color;\n"
					"in vec2 v_TexCoord;\n"
					"void main() {\n"
						"Color = vec4(v_TexCoord, 0, 1); //u_Color; //* texture(u_Texture, v_TexCoord);\n"
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

    /* float vertices[] = {
    	// positions          // colors           // texture coords
    	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   -1.0f, 1.0f,   // top right
    	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   -1.0f, 0.0f,   // bottom right
    	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	}; */

    float verts[] = {
		0.0f, 0.5f, 0.0f, 0.0f, 0.5f,
		0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
		-0.5f, 0.0f, 0.0f, -0.5f, 0.0f
	};

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (void*)(sizeof(float) * 3));



    /* unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;

    unsigned char *data = stbi_load("test.jpg", &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); */

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render
		//glBindTexture(GL_TEXTURE_2D, texture);

        shader.Bind();
		glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.Unbind();

    glfwTerminate();
    return 0;
}