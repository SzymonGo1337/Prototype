#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebufferCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

float y = 200.0f;
float x = 200.0f;
void keyCallback(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	if(glfwGetKey(window, GLFW_KEY_W)) {
		y = y + 4.5f;
	} else if(glfwGetKey(window, GLFW_KEY_S)) {
		y = y - 4.5f;
	}
	
	if(glfwGetKey(window, GLFW_KEY_D)) {
		x = x + 4.5f;
	} else if(glfwGetKey(window, GLFW_KEY_A)) {
		x = x - 4.5f;
	}
}

class Rect {
private:
	float vertices[24];
	float posX, posY;
	float rectSizeX, rectSizeY;
	
public:
	Rect(float sizeX, float sizeY) {
		posX = 200.0f;
		posY = 200.0f;
		
		rectSizeX = sizeX;
		rectSizeY = sizeY;
	}
	
	void setpos(float x, float y) {
		posX = x;
		posY = y;
		
		float test[24] = {
			posX, rectSizeX + posY, 0.0f,
			rectSizeX + posX, rectSizeY + posY, 0.0f,
			rectSizeX + posX, posY, 0.0f,
			posX, posY, 0.0f,
		};
		
		for(int i = 0; i < 23; ++i) {
			vertices[i] = test[i];
		}
	}
	
	void render() {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	
};

/* void render(Rect rect, GLFWwindow* window) {
	keyCallback(window);
		
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
		
	//render
	rect.setpos(x, y);
	rect.render();
	
	glfwSwapBuffers(window);
	glfwPollEvents();
}

double currentTime, lastTime;
void renderfps(double framerate, Rect rect, GLFWwindow* window) {
	currentTime = glfwGetTime();
	if(currentTime - lastTime >- 1.0 / framerate) {
		lastTime = currentTime;
		render(rect, window);
	}
} */

int main() {
	if(!glfwInit()) {
		std::cerr << "GLFW INIT ERROR" << "\n";
		exit(EXIT_FAILURE);
	}
	
	/* glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4); */
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); only MacOS
	
	int width = 1280, height = 720;
	
	GLFWwindow* window = glfwCreateWindow(width, height, "Prototype", nullptr, nullptr);
	if(!window) {
		std::cerr << "GLFW WINDOW ERROR" << "\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebufferCallback);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0, width, 0, height, 0, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	Rect r1(50.0f, 50.0f);
	
	while(!glfwWindowShouldClose(window)) {
		keyCallback(window);
		
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//render
		r1.setpos(x, y);
		r1.render();
	
		glfwSwapBuffers(window);
		glfwPollEvents();

		//renderfps(60, r1, window);
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}