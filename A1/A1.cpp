// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 1
// Feburary 8th 2018

#include <ctime>
#include <iostream>
#include "A1.h"
#include "Globals.h"
#include "Functions/Input.h"
#include "Functions/Render.h"

#define GL_MAJOR 4
#define GL_MINOR 5
#define WINDOW_TITLE "Assignment 1"
#define VERTEX_SHADER_PATH "Shaders/vertex.vert"
#define FRAGMENT_SHADER_PATH "Shaders/fragment.frag"
#define CAMERA_DISTANCE 20.0f
#define CAMERA_ANGLE 30.0f

using std::cout;
using std::endl;

int main()
{
	//If cannot initialize, exit
	if (!init()) { quit(EXIT_FAILURE); }

	//Setup random number generator
	srand(time(nullptr));

	//Camera and Shader
	camera = Camera(CAMERA_DISTANCE, CAMERA_ANGLE);
	shader = Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shader.use();

	//Setup data
	setupCubes();
	setupLines();
	setupAxis();

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Get input events
		glfwPollEvents();

		//Clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Calculate projection * view matrix
		vpMatrix = camera.perspective() * camera.view();

		//Render objects
		renderLines();
		renderAxis();
		renderCubes();

		//Swap buffers
		glfwSwapBuffers(window);
	}

	//Quit
	quit(EXIT_SUCCESS);
}

bool init()
{
	//Opening message
	cout << "Starting OpenGL " << GL_MAJOR << "." << GL_MINOR << " context..." << endl;

	//Initialize GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		//Quit if failed
		cout << "Failed to initialize GLFW!" << endl;
		return false;
	}

	//Set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Set window to resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Create window
	window = glfwCreateWindow(screenWidth, screenHeight, WINDOW_TITLE, nullptr, nullptr);

	//Test to make sure window has correctly been made
	if (window == nullptr)
	{
		//If failed, exit
		cout << "Failed to create a GLFW window!" << endl;
		return false;
	}

	//Set focus to window
	glfwMakeContextCurrent(window);

	//Register window callbacks
	registerCallbacks();

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		//If failed, exit
		cout << "Failed to initialize GLEW!" << endl;
		return false;
	}

	//Setup OpenGL
	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glPointSize(6.0f);
	glEnable(GL_DEPTH_TEST);
	return true;
}

void quit(const int code)
{
	//Cleanup memory
	glDeleteVertexArrays(1, &cubesVAO);
	glDeleteVertexArrays(1, &linesVAO);
	glDeleteVertexArrays(1, &axisVAO);

	glDeleteBuffers(1, &cubesVBO);
	glDeleteBuffers(1, &cubesEBO);
	glDeleteBuffers(1, &linesVBO);
	glDeleteBuffers(1, &axisVBO);

	glUseProgram(0);
	glDeleteProgram(shader.getID());

	//Terminate GLFW
	glfwTerminate();

	//Pause then exit
	system("PAUSE");
	exit(code);
}