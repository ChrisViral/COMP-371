// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#include "Globals.h"

//Screen size
GLint screenWidth = 800;
GLint screenHeight = 800;

//Shader, camera, mesh, shadows
Camera* camera;
Shader* lightingShader, *simpleShader, *shadowsShader;
Mesh* horse;
Light* light;
Shadows* shadows;

//View Projection matrix
glm::mat4 vpMatrix;

//GL Window
GLFWwindow* window;

//Rendering options
bool useTextures = false;
GLenum meshRender = GL_FILL;

//Joints
std::vector<Cube*> joints;