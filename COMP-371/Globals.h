// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Objects/Camera.h"
#include "Objects/Shader.h"
#include "Objects/Mesh.h"
#include "Objects/Light.h"
#include "Objects/Shadows.h"
#include "Objects/Grid.h"

/// \brief GL screen width/height
extern GLint screenWidth, screenHeight;
/// \brief Camera object
extern Camera* camera;
/// \brief Shaders
extern Shader* lightingShader, *simpleShader, *shadowsShader;
/// \brief Horse mesh
extern Mesh* horse;
/// \brief World plane
extern Grid* grid;
/// \brief Light source
extern Light* light;
/// \brief Shadows
extern Shadows* shadows;
/// \brief View matrices
extern glm::mat4 vpMatrix;
/// \brief GL window pointer
extern GLFWwindow* window;
/// \brief If textures should be used when rendering
extern bool useTextures, useShadows, renderHord;
/// \brief Rendering type for the horse mesh
extern GLenum meshRender;
/// \brief Joints, in the correct order
extern std::vector<Cube*> joints;
/// \brief Frame delta time
extern float deltaTime;

/**
 * \brief Calculates the delta time of the last frame and sets it to the deltaTime variable
 */
void calculateDeltaTime();