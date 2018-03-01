// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#include <GL/glew.h>
#include "Input.h"
#include "../Globals.h"
#include "Render.h"

//Mouse sensitivity
#define SENSITIVITY 0.1f

using glm::max;
using glm::vec3;

//Last mouse x and y recorded positions
float lastMouseX = screenWidth / 2.0f;
float lastMouseY = screenHeight / 2.0f;

void registerCallbacks()
{
	//Register all callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Set new screen width and height, then notify GL
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//If the right mouse button is pressed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		//Pan camera from side to side
		camera.panCamera((lastMouseX - xpos) * SENSITIVITY);
	}
	//If the middle mouse button is pressed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		//Tilt camera up and down
		camera.tiltCamera((ypos - lastMouseY) * SENSITIVITY);
	}
	//If the left mouse button is pressed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		//Zoom in and out
		camera.adjustDistance((ypos - lastMouseY) * SENSITIVITY);
	}

	//Set new last mouse positions
	lastMouseX = xpos;
	lastMouseY = ypos;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//If the action is not a keypress, return
	if (!action == GLFW_PRESS) { return;  }

	//If the shift key is being pressed
	if (mods & GLFW_MOD_SHIFT)
	{
		switch (key)
		{
			//W - Pitch up 5 degrees
		case GLFW_KEY_W:
			pitchAngle += 5.0f; break;

			//S - Pitch down 5 degrees
		case GLFW_KEY_S:
			pitchAngle -= 5.0f; break;

			//A - Yaw left 5 degrees
		case GLFW_KEY_A:
			yawAngle += 5.0f; break;

			//D - Yaw right 5 degrees
		case GLFW_KEY_D:
			yawAngle -= 5.0f; break;

		default:
			break;
		}
	}
	//If the shift key isn't pressed
	else
	{
		switch (key)
		{
			//Escape - close window
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true); break;

			//Home - reset world
		case GLFW_KEY_HOME:
		{
			offset = vec3(0.0f);
			yawAngle = 0.0f;
			pitchAngle = 0.0f;
			size = 1.0f;
			camera.reset();
			break;
		}

		//Space - randomly position horse
		case GLFW_KEY_SPACE:
			offset = vec3(randomRange(-50, 50), 0.0f, randomRange(-50, 50)); break;

			//U - scale up horse
		case GLFW_KEY_U:
			size += 0.1f; break;

			//J - scale down horse
		case GLFW_KEY_J:
			//Get the max to prevent <=0 sizes
			size = max(0.1f, size - 0.1f); break;

			//P - render as points
		case GLFW_KEY_P:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;

			//T - render as triangles
		case GLFW_KEY_T:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;

			//L - render as lines
		case GLFW_KEY_L:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;

			//W - move horse up
		case GLFW_KEY_W:
			offset.z -= 1.0f; break;

			//S - move horse down
		case GLFW_KEY_S:
			offset.z += 1.0f; break;

			//A - move horse left
		case GLFW_KEY_A:
			offset.x -= 1.0f; break;

			//D - move horse right
		case GLFW_KEY_D:
			offset.x += 1.0f; break;

			//Up - move camera up
		case GLFW_KEY_UP:
			camera.moveTarget(vec3(0.0f, 0.0f, -1.0f)); break;

			//Down - move camera down
		case GLFW_KEY_DOWN:
			camera.moveTarget(vec3(0.0f, 0.0f, 1.0f)); break;

			//Left - move camera left
		case GLFW_KEY_LEFT:
			camera.moveTarget(vec3(-1.0f, 0.0f, 0.0f)); break;

			//Right - move camera right
		case GLFW_KEY_RIGHT:
			camera.moveTarget(vec3(1.0f, 0.0f, 0.0f)); break;

			//Other keys - do nothing
		default:
			break;
		}
	}
	
}

int randomRange(const int min, const int max)
{
	//Return a random value between min and max
	return (rand() % (max - min + 1)) + min;
}