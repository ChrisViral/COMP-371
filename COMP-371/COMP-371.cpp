// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#include <ctime>
#include <iostream>
#include "COMP-371.h"
#include "Globals.h"
#include "Functions/Input.h"
#include "Parsers/MeshParser.h"
#include "Objects/Grid.h"
#include "Objects/Axis.h"
#include "Objects/Light.h"
#include "Objects/Shadows.h"

#define GL_MAJOR 4
#define GL_MINOR 5
#define WINDOW_TITLE "COMP-371 Assignment 2"
#define MESH_PATH "Meshes/horse.mesh"
#define LIGHTING_VERTEX_SHADER_PATH "Shaders/lightVertex.vert"
#define LIGHTING_FRAGMENT_SHADER_PATH "Shaders/lightFragment.frag"
#define SIMPLE_VERTEX_SHADER_PATH "Shaders/simpleVertex.vert"
#define SIMPLE_FRAGMENT_SHADER_PATH "Shaders/simpleFragment.frag"
#define SHADOWS_VERTEX_SHADER_PATH "Shaders/shadowVertex.vert"
#define SHADOWS_FRAGMENT_SHADER_PATH "Shaders/shadowFragment.frag"
#define CAMERA_DISTANCE 20.0f
#define CAMERA_ANGLE 30.0f
#define GRID_SIZE 50
#define AXIS_SIZE 5
#define LIGHT_POSITION vec3(0.0f, 20.0f, 0.0f)
#define LIGHT_COLOUR vec3(1.0f)
#define AMBIENT_STRENGTH 0.2f
#define SPECULAR_STRENGTH 0.5f

using glm::vec3;
using glm::mat4;
using std::cout;
using std::endl;
using std::vector;

static bool loaded = false;
static vector<Object*> objects;
static const int CLEAR_BIT = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

int main()
{
	//If cannot initialize, exit
	if (!init()) { quit(EXIT_FAILURE); }

	//Setup random number generator
	srand(time(nullptr));

	//Camera and Shader
	camera = new Camera(CAMERA_DISTANCE, CAMERA_ANGLE);
	lightingShader = new Shader(LIGHTING_VERTEX_SHADER_PATH, LIGHTING_FRAGMENT_SHADER_PATH);
	simpleShader = new Shader(SIMPLE_VERTEX_SHADER_PATH, SIMPLE_FRAGMENT_SHADER_PATH);
	shadowsShader = new Shader(SHADOWS_VERTEX_SHADER_PATH, SHADOWS_FRAGMENT_SHADER_PATH);
	lightingShader->use();
	lightingShader->setInt("state", 0);

	//Parse mesh
	horse = MeshParser(MESH_PATH).parse();
	light = new Light(LIGHT_POSITION);
	grid = new Grid(GRID_SIZE);

	//Add objects to vector
	objects.push_back(horse);
	objects.push_back(light);
	objects.push_back(grid);
	objects.push_back(new Axis(AXIS_SIZE));

	//Setup objects
	for (Object* o : objects)
	{
		o->setup();
	}

	//Setup shadows
	shadows = new Shadows(light);

	loadJoints();
	loaded = true;

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Get input events 
		glfwPollEvents();

		if (useShadows)
		{
			//Setup shadows
			shadowsShader->use();
			lightSpaceMatrix = shadows->view() * shadows->projection();
			vpMatrix = lightSpaceMatrix;
			shadowsShader->setMat4("vpMat", vpMatrix);
			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

			//Render shadows
			glBindFramebuffer(GL_FRAMEBUFFER, shadows->getFBO());
			glClear(GL_DEPTH_BUFFER_BIT);

			//Only render shadows for grid and horse
			horse->render(shadowsShader);
			grid->render(shadowsShader);

			//Unbind frame buffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
			//Reset view
			glViewport(0, 0, screenWidth, screenHeight);
		}

		//Clear buffers
		glClear(CLEAR_BIT);

		//Calculate projection * view matrix
		vpMatrix = camera->perspective() * camera->view();

		//Render objects
		renderAll();

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
	glfwSwapInterval(1);

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

void loadJoints()
{
	joints.push_back(horse->findCube("head"));
	joints.push_back(horse->findCube("neck"));
	joints.push_back(horse->findCube("urf_leg"));
	joints.push_back(horse->findCube("lrf_leg"));
	joints.push_back(horse->findCube("urb_leg"));
	joints.push_back(horse->findCube("lrb_leg"));
	joints.push_back(horse->findCube("ulf_leg"));
	joints.push_back(horse->findCube("llf_leg"));
	joints.push_back(horse->findCube("ulb_leg"));
	joints.push_back(horse->findCube("llb_leg"));
}

void renderAll(Shader* shader)
{
	for (Object* o : objects)
	{
		o->render(shader);
	}
}

void quit(const int code)
{
	if (loaded)
	{
		//Delete render objects
		for (Object* o : objects)
		{
			delete o;
		}
		objects.clear();
		horse = nullptr;
		light = nullptr;

		//Delete camera and lightingShader
		delete camera;
		delete lightingShader;
		delete simpleShader;
		delete shadowsShader;
		delete shadows;
		camera = nullptr;
		lightingShader = nullptr;
		simpleShader = nullptr;
		shadowsShader = nullptr;
		shadows = nullptr;
	}

	//Terminate GLFW
	glfwTerminate();

	//Pause then exit
	system("PAUSE");
	exit(code);
}
