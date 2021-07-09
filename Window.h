#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>



class Window {
	public:
		Window();
		Window(GLint windowWidth, GLint windowHeight);

		int initialize();

		GLfloat getBufferWidth() { return bufferWidth;  }
		GLfloat getBufferHeight() { return bufferHeight;  }
		bool getShouldClose() { return glfwWindowShouldClose(mainWindow);  }
		void swapBuffers() { glfwSwapBuffers(mainWindow); }

		GLFWwindow *mainWindow;

		~Window();

	private:
		GLint width, height;
		GLint bufferWidth, bufferHeight;
};

	