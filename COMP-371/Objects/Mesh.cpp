#include "Mesh.h"

using glm::vec3;

GLfloat Mesh::vertices[] =
{
	//Front face
	 0.5f,  0.5f,  0.5f, //Top right
	 0.5f, -0.5f,  0.5f, //Bottom right
	-0.5f, -0.5f,  0.5f, //Bottom left
	-0.5f,  0.5f,  0.5f, //Top left

	//Back face
	 0.5f,  0.5f, -0.5f, //Top right
	 0.5f, -0.5f, -0.5f, //Bottom right
	-0.5f, -0.5f, -0.5f, //Bottom left
	-0.5f,  0.5f, -0.5f, //Top left
};

GLint Mesh::indices[] =
{
	0, 3, 1, //Front face
	1, 3, 2,

	0, 1, 4, //Right face
	4, 1, 5,

	6, 3, 7, //Left face
	2, 3, 6,

	5, 6, 4, //Back face
	4, 6, 7,

	0, 4, 3, //Top face
	3, 4, 7,

	1, 6, 5, //Bottom face
	2, 6, 1
};

Mesh::Mesh() : root(nullptr), position(vec3(0.0f)), scale(0), xRot(0), zRot(0) { }

Mesh::~Mesh()
{
	delete root;
	root = nullptr;
}
