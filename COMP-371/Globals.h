// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Objects/Camera.h"
#include "Objects/Shader.h"
#include "Objects/Mesh.h"
#include "Objects/Light.h"

/// \brief GL screen width
extern GLint screenWidth;
/// \brief GL screen Height
extern GLint screenHeight;
/// \brief Camera object
extern Camera* camera;
/// \brief Shader program
extern Shader* lightingShader, *simpleShader;
/// \brief Horse mesh
extern Mesh* horse;
/// \brief Light source
extern Light* light;
/// \brief Projection * View matrix
extern glm::mat4 vpMatrix;
/// \brief GL window pointer
extern GLFWwindow* window;
/// \brief If textures should be used when rendering
extern bool useTextures;
/// \brief Rendering type for the horse mesh
extern GLenum meshRender;
/// \brief Joints, in the correct order
extern std::vector<Cube*> joints;