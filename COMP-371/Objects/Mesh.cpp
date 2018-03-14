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
	//Front face			Texture coords
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, //Top right
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, //Bottom right
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, //Bottom left
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, //Top left

	//Back face				Texture coords
	 0.5f,  0.5f, -0.5f,	1.0f, 0.0f, //Top right
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, //Bottom right
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, //Bottom left
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f,  //Top left

	//Sides (texture fix)
	 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, //Top right
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, //Bottom right
	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, //Bottom left
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f  //Top left
};

const GLint Mesh::indices[] =
{
	0, 3, 1, //Front face
	1, 3, 2,

	0, 1, 8, //Right face
	8, 1, 9,

	10, 3, 11, //Left face
	2, 3, 10,

	5, 6, 4, //Back face
	4, 6, 7,

	0, 4, 3, //Top face
	3, 4, 7,

	1, 6, 5, //Bottom face
	2, 6, 1
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		glEnableVertexAttribArray(0);

		//Setup the texture vertex attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nrChannels;
		unsigned char* data = stbi_load(TEXTURE_PATH, &width, &height, &nrChannels, 0);
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

		shader->setInt("tex2", 1);

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//Raise set flag
		set = true;
	}
}

void Mesh::render() const
{
	//Constant values for the rendering
	static const vec3 yAxis(0.0f, 1.0f, 0.0f);
	static const vec3 zAxis(0.0f, 0.0f, 1.0f);

	//Nothing to render if no root or not set
	if (root == nullptr || !set) { return; }

	glPolygonMode(GL_FRONT_AND_BACK, meshRender);

	if (useTextures)
	{
		shader->setInt("state", 2);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex);
	}
	else { shader->setInt("state", 0); }

	mat4 model(1.0f);
	model = translate(model, vec3(position.x, position.y * scaleFactor, position.z));	//Horse position on the grid
	model = rotate(model, radians(yRot), yAxis);	//Yaw (side) rotation of the horse
	model = rotate(model, radians(zRot), zAxis);	//Pitch (vertical) rotation of the horse
	model = scale(model, size * scaleFactor);		//Scale factor of the horse

	//Rendering setup
	glBindVertexArray(VAO);
	glLineWidth(3.0f);

	//Render starting at the root
	root->render(model);

	//Rendering end
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
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
