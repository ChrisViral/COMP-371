// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#include <GL/glew.h>
#include <iostream>
#include "Input.h"
#include "../Globals.h"
#include "Random.h"

//Mouse sensitivity
#define SENSITIVITY 0.1f

using std::cerr;
using std::endl;
using glm::max;
using glm::vec3;

//Last mouse x and y recorded positions
static float lastMouseX = screenWidth / 2.0f;
static float lastMouseY = screenHeight / 2.0f;

void registerCallbacks()
{
	//Register all callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetErrorCallback(error_callback);
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
		camera->panCamera((lastMouseX - xpos) * SENSITIVITY);
	}
	//If the middle mouse button is pressed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		//Tilt camera up and down
		camera->tiltCamera((ypos - lastMouseY) * SENSITIVITY);
	}
	//If the left mouse button is pressed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		//Zoom in and out
		camera->adjustDistance((ypos - lastMouseY) * SENSITIVITY);
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
			horse->zRot += 5.0f; break;

			//S - Pitch down 5 degrees
		case GLFW_KEY_S:
			horse->zRot -= 5.0f; break;

			//A - Yaw left 5 degrees
		case GLFW_KEY_A:
			horse->yRot += 5.0f; break;

			//D - Yaw right 5 degrees
		case GLFW_KEY_D:
			horse->yRot -= 5.0f; break;

			//0 - Rotate joint 0 by -5 degrees
		case GLFW_KEY_0:
			joints[0]->angle -= 5.0f; break;

			//1 - Rotate joint 1 by -5 degrees
		case GLFW_KEY_1:
			joints[1]->angle -= 5.0f; break;

			//2 - Rotate joint 2 by -5 degrees
		case GLFW_KEY_2:
			joints[2]->angle -= 5.0f; break;

			//3 - Rotate joint 3 by -5 degrees
		case GLFW_KEY_3:
			joints[3]->angle -= 5.0f; break;

			//4 - Rotate joint 4 by -5 degrees
		case GLFW_KEY_4:
			joints[4]->angle -= 5.0f; break;

			//5 - Rotate joint 5 by -5 degrees
		case GLFW_KEY_5:
			joints[5]->angle -= 5.0f; break;

			//6 - Rotate joint 6 by -5 degrees
		case GLFW_KEY_6:
			joints[6]->angle -= 5.0f; break;

			//7 - Rotate joint 7 by -5 degrees
		case GLFW_KEY_7:
			joints[7]->angle -= 5.0f; break;

			//8 - Rotate joint 8 by -5 degrees
		case GLFW_KEY_8:
			joints[8]->angle -= 5.0f; break;

			//9 - Rotate joint 9 by -5 degrees
		case GLFW_KEY_9:
			joints[9]->angle -= 5.0f; break;

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
			horse->reset();
			camera->reset();
			//Reset all joints too
			for (Cube* c : joints)
			{
				c->angle = c->startAngle;
			}
			break;
		}

		//Space - randomly position horse
		case GLFW_KEY_SPACE:
			horse->position = vec3(randomRange(-50, 50), horse->position.y, randomRange(-50, 50)); break;

			//U - scale up horse
		case GLFW_KEY_U:
			horse->scaleFactor += 0.1f; break;

			//J - scale down horse
		case GLFW_KEY_J:
			//Get the max to prevent <=0 sizes
			horse->scaleFactor = max(0.1f, horse->scaleFactor - 0.1f); break;

			//P - render as points
		case GLFW_KEY_P:
			meshRender = GL_POINT; break;

			//T - render as triangles
		case GLFW_KEY_T:
			meshRender = GL_FILL; break;

			//L - render as lines
		case GLFW_KEY_L:
			meshRender = GL_LINE; break;

			//W - move horse up
		case GLFW_KEY_W:
			horse->position.z -= 1.0f; break;

			//S - move horse down
		case GLFW_KEY_S:
			horse->position.z += 1.0f; break;

			//A - move horse left
		case GLFW_KEY_A:
			horse->position.x -= 1.0f; break;

			//D - move horse right
		case GLFW_KEY_D:
			horse->position.x += 1.0f; break;

			//Up - move camera up
		case GLFW_KEY_UP:
			camera->moveTarget(vec3(0.0f, 0.0f, -1.0f)); break;

			//Down - move camera down
		case GLFW_KEY_DOWN:
			camera->moveTarget(vec3(0.0f, 0.0f, 1.0f)); break;

			//Left - move camera left
		case GLFW_KEY_LEFT:
			camera->moveTarget(vec3(-1.0f, 0.0f, 0.0f)); break;

			//Right - move camera right
		case GLFW_KEY_RIGHT:
			camera->moveTarget(vec3(1.0f, 0.0f, 0.0f)); break;

			//B - Toggle texture rendering
		case GLFW_KEY_B:
			useTextures = !useTextures; break;

			//X - Togle shadows rendering
		case GLFW_KEY_X:
			useShadows = !useShadows; break;

			//0 - Rotate joint 0 by 5 degrees
		case GLFW_KEY_0:
			joints[0]->angle += 5.0f; break;

			//1 - Rotate joint 1 by 5 degrees
		case GLFW_KEY_1:
			joints[1]->angle += 5.0f; break;

			//2 - Rotate joint 2 by 5 degrees
		case GLFW_KEY_2:
			joints[2]->angle += 5.0f; break;

			//3 - Rotate joint 3 by 5 degrees
		case GLFW_KEY_3:
			joints[3]->angle += 5.0f; break;

			//4 - Rotate joint 4 by 5 degrees
		case GLFW_KEY_4:
			joints[4]->angle += 5.0f; break;

			//5 - Rotate joint 5 by 5 degrees
		case GLFW_KEY_5:
			joints[5]->angle += 5.0f; break;

			//6 - Rotate joint 6 by 5 degrees
		case GLFW_KEY_6:
			joints[6]->angle += 5.0f; break;

			//7 - Rotate joint 7 by 5 degrees
		case GLFW_KEY_7:
			joints[7]->angle += 5.0f; break;

			//8 - Rotate joint 8 by 5 degrees
		case GLFW_KEY_8:
			joints[8]->angle += 5.0f; break;

			//9 - Rotate joint 9 by 5 degrees
		case GLFW_KEY_9:
			joints[9]->angle += 5.0f; break;

			//Other keys - do nothing
		default:
			break;
		}
	}
	
}

void error_callback(int error, const char* description)
{
	//Output to console
	cerr << "GLFW error code " << error << " encountered\n" << description << endl;
}