// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#include "Globals.h"

//Screen size
GLint screenWidth = 800;
GLint screenHeight = 800;

//Shader, camera, mesh, shadows, light
Camera* camera;
Shader* lightingShader, *simpleShader, *shadowsShader;
Mesh* horse;
Grid* grid;
Light* light;
Shadows* shadows;

//View Projection matrix
glm::mat4 vpMatrix;

//GL Window
GLFWwindow* window;

//Rendering options
bool useTextures = false, useShadows = true, renderHord = false;
GLenum meshRender = GL_FILL;

//Joints
std::vector<Cube*> joints;

float deltaTime = 0.0f;
static float lastTime = 0.0f;
void calculateDeltaTime()
{
	const float time = glfwGetTime();
	deltaTime = time - lastTime;
	lastTime = time;
}
