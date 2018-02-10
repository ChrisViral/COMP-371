// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 1
// Feburary 8th 2018

#include <glm/glm.hpp>
#include "Globals.h"

using glm::mat4;

//Screen size
GLint screenWidth = 800;
GLint screenHeight = 800;

//Shader/Camera
Camera camera;
Shader shader;

//GL Window
GLFWwindow* window;

//GL containers
GLuint cubesVAO, cubesVBO, cubesEBO;
GLuint linesVAO, linesVBO;
GLuint axisVAO, axisVBO;

//View Projection matrix
mat4 vpMatrix;