#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <stb/stb_image.h>
#include <iostream>
#include <stack>
#include "Mesh.h"
#include "../Globals.h"

#define TEXTURE_PATH "Textures/horse.png"

using glm::radians;
using glm::vec3;
using glm::mat4;
using std::cout;
using std::endl;
using std::stack;

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

Mesh::Mesh() : Object(), root(nullptr), position(vec3(0.0f)), size(vec3(0.0f)), scaleFactor(1.0f), yRot(0.0f), zRot(0.0f) { }

Mesh::~Mesh()
{
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

		lightingShader->setInt("tex2", 1);

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//Raise set flag
		set = true;
	}
}

void Mesh::render(Shader* shader) const
{
	//Constant values for the rendering
	static const vec3 yAxis(0.0f, 1.0f, 0.0f);
	static const vec3 zAxis(0.0f, 0.0f, 1.0f);
	static const vec3 ambient(0.2f, 0.1f, 0.05f);
	static const vec3 diffuse(0.7f, 0.25f, 0.1f);
	static const vec3 specular(0.25f, 0.15f, 0.1f);
	static const float shininess = 13.0f;

	//Nothing to render if no root or not set
	if (root == nullptr || !set) { return; }

	//Rendering setup
	glBindVertexArray(VAO);
	glLineWidth(3.0f);

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

	if (shader == nullptr)
	{
		shader = lightingShader;
		shader->use();
		shader->setMat4("vpMat", vpMatrix);
		shader->setVec3("cameraPosition", camera->getPosition());

		if (useShadows)
		{
			shader->setBool("useShadows", true);
			shader->setMat4("lightSpace", lightSpaceMatrix);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, shadows->getDepthMap());
		}
		else { shader->setBool("useShadows", false); }

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


	mat4 model(1.0f);
	model = translate(model, vec3(position.x, position.y * scaleFactor, position.z));	//Horse position on the grid
	model = rotate(model, radians(yRot), yAxis);	//Yaw (side) rotation of the horse
	model = rotate(model, radians(zRot), zAxis);	//Pitch (vertical) rotation of the horse
	model = scale(model, size * scaleFactor);		//Scale factor of the horse

	//Render starting at the root
	root->render(model, shader);

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
