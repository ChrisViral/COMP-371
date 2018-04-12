// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <stb/stb_image.h>
#include <iostream>
#include <stack>
#include <vector>
#include "Mesh.h"
#include "../Globals.h"
#include "../Functions/Random.h"
#include "../COMP-371.h"

#define TEXTURE_PATH "Textures/horse.png"

using glm::max;
using glm::radians;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using std::cout;
using std::endl;
using std::stack;
using std::vector;

const GLfloat Mesh::vertices[] =
{
	//Front face			Normal					Texture
	-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f, 0.0f, //Bottom left
	 0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		1.0f, 0.0f, //Bottom right
	 0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		1.0f, 1.0f, //Top right
	-0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f, 1.0f, //Top left

	//Right face
	 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 0.0f, //Bottom left
	 0.5f,  0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f, //Bottom right
	 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 1.0f, //Top right
	 0.5f, -0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f, //Top left

	//Left face
	-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,		0.0f, 0.0f, //Bottom left
	-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,		1.0f, 0.0f, //Bottom right
	-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,		1.0f, 1.0f, //Top right
	-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,		0.0f, 1.0f, //Top left

	//Back face
	-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f, //Bottom left
	 0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f, //Bottom right
	 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f, //Top right
	-0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f, //Top left

	//Top face
	-0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f, //Bottom left
	 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f, //Bottom right
	 0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 1.0f, //Top right
	-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f, //Top left

	//Bottom face
	-0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f, //Bottom left
	 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f, //Bottom right
	 0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 1.0f, //Top right
	-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f  //Top left
};

const GLint Mesh::indices[] =
{
	0, 1, 2,	//Front face
	0, 2, 3,

	5, 4, 7,	//Right face
	5, 7, 6,

	11, 8, 9,	//Left face
	11, 9, 10,

	12, 15, 14,	//Back face
	12, 14, 13,

	16, 17, 18,	//Top face
	16, 18, 19,

	23, 22, 21,	//Bottom face
	23, 21, 20
};

const vec4 Mesh::points[] = 
{
	vec4( 0.5f,  0.5f,  0.5f, 1.0f),
	vec4(-0.5f,  0.5f,  0.5f, 1.0f),
	vec4( 0.5f, -0.5f,  0.5f, 1.0f),
	vec4(-0.5f, -0.5f,  0.5f, 1.0f),
	vec4( 0.5f,  0.5f, -0.5f, 1.0f),
	vec4(-0.5f,  0.5f, -0.5f, 1.0f),
	vec4( 0.5f, -0.5f, -0.5f, 1.0f),
	vec4(-0.5f, -0.5f, -0.5f, 1.0f)
};

Mesh::Mesh() : Object(), root(nullptr), collider(new Collider(this)), animation(new Animation(this)),
			   position(vec3(0.0f)), size(vec3(0.0f)), scaleFactor(1.0f), yRot(0.0f), zRot(0.0f) { }

Mesh::Mesh(const Mesh& mesh) : Object(), scaleFactor(mesh.scaleFactor), yRot(mesh.yRot), zRot(mesh.zRot)
{
	start = mesh.start;
	root = new Cube(*mesh.root, this);
	collider = new Collider(*mesh.collider, this);
	animation = new Animation(*mesh.animation, this);
	position = vec3(mesh.position);
	size = vec3(mesh.size);
}

Mesh::~Mesh()
{
	//Delete the collider and animation
	delete collider;
	delete animation;

	//Delete root cube if any
	if (root != nullptr)
	{
		delete root;
		root = nullptr;
	}
	//Clear buffers and arrays if set
	if (set)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteTextures(1, &tex);
	}
}

void Mesh::setup()
{
	//Only proceed if not set yet
	if (!set)
	{
		//This VAO/VBO/EBO setup is adapted from https://learnopengl.com/Getting-started/Hello-Triangle

		//Setup start state
		start.position = vec3(position);
		start.yRot = yRot;
		start.zRot = zRot;

		//Generate containers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//Bind VAO
		glBindVertexArray(VAO);

		//Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//Setup the position vertex attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		glEnableVertexAttribArray(0);

		//Setup normal vector vertex attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//Setup the texture vertex attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		//Load texture
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nrChannels;
		stbi_uc* data = stbi_load(TEXTURE_PATH, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			cout << "Failed to load texture at " << TEXTURE_PATH << endl;
		}
		stbi_image_free(data);

		//Set texture location
		lightingShader->setInt("tex2", 1);

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//Get all points of the mesh
		vector<vec3> points;
		root->fillPoints(calculateModelMatrix(), points);

		//Get furthest point from center of the mesh
		float radius = 0.0f;
		for (const vec3 p : points)
		{
			radius = max(radius, length(position - p));
		}

		//Set collider radius
		collider->setRadius(radius * 0.8f);

		//Raise set flag
		set = true;
	}
}

void Mesh::render(Shader* shader) const
{
	//Constant values for the rendering
	static const vec3 ambient(0.2f, 0.1f, 0.05f);
	static const vec3 diffuse(0.7f, 0.25f, 0.1f);
	static const vec3 specular(0.25f, 0.15f, 0.1f);
	static const float shininess = 13.0f;

	//Nothing to render if no root or not set
	if (root == nullptr || !set) { return; }

	//Rendering setup
	glBindVertexArray(VAO);
	glLineWidth(3.0f);

	//Face culling if rendering as cubes
	if (meshRender == GL_FILL)
	{
		glEnable(GL_CULL_FACE);
		if (shader == shadowsShader)
		{
			glCullFace(GL_FRONT);
		}
	}
	//No shadows for lines or points
	else if (shader == shadowsShader) { return; }

	//Setup render mode
	glPolygonMode(GL_FRONT_AND_BACK, meshRender);

	//Get shader if none specified
	if (shader == nullptr)
	{
		shader = lightingShader;
		shader->use();
		shader->setMat4("vpMat", vpMatrix);
		shader->setVec3("cameraPosition", camera->getPosition());

		//Set shadow texture
		if (useShadows)
		{
			shader->setBool("useShadows", true);
			shader->setFloat("farPlane", SHADOWS_FAR_PLANE);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_CUBE_MAP, shadows->getCubeMap());
		}
		else { shader->setBool("useShadows", false); }

		//Set material properties if using textures
		if (useTextures)
		{
			shader->setInt("state", 2);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex);
			shader->setVec3("material.ambient", ambient);
			shader->setVec3("material.diffuse", diffuse);
			shader->setVec3("material.specular", specular);
			shader->setFloat("material.shininess", shininess);
		}
		else
		{
			shader->setInt("state", 0);
			shader->setVec3("material.ambient", Object::ambient);
			shader->setVec3("material.diffuse", Object::diffuse);
			shader->setVec3("material.specular", Object::specular);
			shader->setFloat("material.shininess", Object::shininess);
		}
	}

	//Animate model
	if (renderHord) { animation->animate(); }

	//Render starting at the root
	root->render(calculateModelMatrix(), shader);

	//Rendering end
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
}

void Mesh::reset()
{
	position = start.position;
	yRot = start.yRot;
	zRot = start.zRot;
	scaleFactor = 1.0f;
}

Cube* Mesh::findCube(const std::string& name) const
{
	//Return null if no root
	if (root == nullptr) { return nullptr; }

	//Setup stack
	stack<Cube*> search;
	search.push(root);

	//Keep searching until empty
	while (!search.empty())
	{
		//Get top cube
		Cube* c = search.top();
		search.pop();

		//Return if name matches
		if (c->getName() == name) { return c; }

		//Add children
		for (Cube* child : c->getChildren())
		{
			search.push(child);
		}
	}

	//Nothing found, return null
	cout << "Cube of name " << name << " could not be found" << endl;
	return nullptr;
}

mat4 Mesh::calculateModelMatrix() const
{
	//Rotation axises
	static const vec3 yAxis(0.0f, 1.0f, 0.0f);
	static const vec3 zAxis(0.0f, 0.0f, 1.0f);

	//World position of the Mesh
	mat4 model(1.0f);
	model = translate(model, vec3(position.x, position.y * scaleFactor, position.z));	//Horse position on the grid
	model = rotate(model, radians(yRot), yAxis);	//Yaw (side) rotation of the horse
	model = rotate(model, radians(zRot), zAxis);	//Pitch (vertical) rotation of the horse
	model = scale(model, size * scaleFactor);		//Scale factor of the horse
	return model;
}

void Mesh::randomize()
{
	//Randomize position
	bool valid;
	do
	{
		position = vec3(randomRange(-40, 40), position.y, randomRange(-40, 40));
		valid = true;
		for (int i = 0; i < HORSE_COUNT; i++)
		{
			//Make sure the horse is not too close to other horses
			Mesh* h = hord[i];
			if (h == nullptr || h == this) { break; }
			if (length(position - h->position) < 8.0f) { valid = false; break; }
		}
	} 
	while (!valid);
	scaleFactor = randomRangef(0.8f, 1.2f);
	yRot = randomRangef(-180.0f, 180.0f);

	//Randomize animation
	animation->speed = randomRangef(0.5f, 2.0f);
	animation->steps = randomRange(2, 10);
	animation->rotSpeed = randomRange(20, 90) * randomSign();
	animation->rotation = randomRange(20, 90);
	animation->waitTime = randomRangef(0.5f, 2.0f);
}