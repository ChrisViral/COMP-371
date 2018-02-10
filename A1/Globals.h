// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 1
// Feburary 8th 2018

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Shader.h"

/// \brief GL screen width
extern GLint screenWidth;
/// \brief GL screen Height
extern GLint screenHeight;
/// \brief Camera object
extern Camera camera;
/// \brief Shader program
extern Shader shader;
/// \brief GL window pointer
extern GLFWwindow* window;
/// \brief Cubes GL containers
extern GLuint cubesVAO, cubesVBO, cubesEBO;
/// \brief Lines GL containers
extern GLuint linesVAO, linesVBO;
/// \brief Axises GL containers
extern GLuint axisVAO, axisVBO;
/// \brief Current projection * view matrix
extern glm::mat4 vpMatrix;