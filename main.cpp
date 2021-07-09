#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"


const float toRadians = 3.14159265358979323846f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

long double centerX = 0.0;
long double centerY = 0.0;
float centerXhi = 0.0;
float centerXlo = 0.0;
float centerYhi = 0.0;
float centerYlo = 0.0;
long double zoom = 1.0;
float zoomHi = 0.0;
float zoomLo = 1.0;
int axisOn = 0;
int ctrDown = 0;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";


//****************************************
//
// createObjects
//
//****************************************

void createObjects() {

	unsigned int indices[] = {
	//  2---,1
	//  | .' |
	//  0'---3
		0, 1, 2,
		0, 3, 1
	};

	GLfloat vertices[] = {
	//    x      y      z   
		-1.0f, -1.0f, -0.0f,
		 1.0f,  1.0f, -0.0f,
		-1.0f,  1.0f, -0.0f,
		 1.0f, -1.0f, -0.0f
	};

	Mesh *obj1 = new Mesh();
	obj1->createMesh(vertices, indices, 12, 6);
	meshList.push_back(obj1);
}



//****************************************
//
// createShaders
//
//****************************************

void createShaders() {

	Shader *shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


//****************************************
//
// renderFract
//
//****************************************

void renderFract() {
	
	// Clear window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderList[0].useShader();
	shaderList[0].setFloat("resX", mainWindow.getBufferWidth());
	shaderList[0].setFloat("resY", mainWindow.getBufferHeight());
	shaderList[0].setFloat("zoomHi", zoomHi);
	shaderList[0].setFloat("zoomLo", zoomLo);
	shaderList[0].setFloat("centerXhi", centerXhi);
	shaderList[0].setFloat("centerXlo", centerXlo);
	shaderList[0].setFloat("centerYhi", centerYhi);
	shaderList[0].setFloat("centerYlo", centerYlo);
	shaderList[0].setInteger("axisOn", axisOn);

	meshList[0]->renderMesh();

	mainWindow.swapBuffers();
}


void splitDouble(long double value, float *high, float *low) {
	
	double delta;

	*high = float(value);
	delta = value - double (*high);
	*low = float(delta);
}



//****************************************
//
//  keyCallback
//
//****************************************

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

	long double pan = 0.05;
	
	if (key ==  GLFW_KEY_ESCAPE && action == GLFW_PRESS) {

        glfwSetWindowShouldClose(window, true);
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS) {

		if (axisOn == 0) {
			axisOn = 1;
		} else {
			axisOn = 0;
		}

		//renderFract();
	}

	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)) {

		centerY = (centerY + pan * zoom);
		splitDouble(centerY, &centerYhi, &centerYlo);
		
		//renderFract();
	}
		
	if (key ==  GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)) {

		centerY = (centerY - pan * zoom);
		splitDouble(centerY, &centerYhi, &centerYlo);
		
		//renderFract();
	}

	if (key ==  GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
    
		centerX = (centerX - pan * zoom);
		splitDouble(centerX, &centerXhi, &centerXlo);
		
		//renderFract();
	}

	if (key ==  GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {

		centerX = (centerX + pan * zoom);
		splitDouble(centerX, &centerXhi, &centerXlo);
		
		//renderFract();
	}

	if (key ==  GLFW_KEY_O && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
    
        zoom = zoom * 1.04;

        if (zoom > 1.0) {

            zoom = 1.0;
        }

		splitDouble(zoom, &zoomHi, &zoomLo);

		//renderFract();
	}

	if (key ==  GLFW_KEY_I && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		
		zoom = zoom * 0.96;
		
		splitDouble(zoom, &zoomHi, &zoomLo);
		
		//renderFract();
    	}
	
	renderFract();
}




//****************************************
//
// main
//
//****************************************

int main() {

	mainWindow = Window(int(0.75 * 1080.0), 1080);
	mainWindow.initialize();

	createObjects();
	createShaders();

	//GLuint uniformProjection = 0, uniformModel = 0;
	//glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	glfwSwapInterval(0);
	glfwSetKeyCallback(mainWindow.mainWindow, keyCallback);

	renderFract();

	while (!mainWindow.getShouldClose()) {
	
		// Get and handle user input events
		glfwPollEvents();
	}
	
	return 0;
}
