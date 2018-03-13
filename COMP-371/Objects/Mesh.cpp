#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Mesh.h"

using glm::radians;
using glm::vec3;
using glm::mat4;

const vec3 Mesh::yAxis = vec3(0.0f, 1.0f, 0.0f);
const vec3 Mesh::zAxis = vec3(0.0f, 0.0f, 1.0f);

const GLfloat Mesh::vertices[] =
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

const GLint Mesh::indices[] =
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

Mesh::Mesh() : VAO(0), VBO(0), EBO(0), set(false), root(nullptr), position(vec3(0.0f)), size(0.0f), yRot(0.0f), zRot(0.0f)
{
	start.position = vec3(position);
	start.size = size;
	start.yRot = yRot;
	start.zRot = zRot;
}

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
	}
}

void Mesh::setup()
{
	//Only proceed if not set yet
	if (!set)
	{
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		glEnableVertexAttribArray(0);

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//Raise set flag
		set = true;
	}
}

vec3 Mesh::getJointAxis() const
{
	//Rotate the joint axis (z axis) around the Y axis
	return rotateY(zAxis, yRot);
}

void Mesh::renderMesh() const
{
	//Nothing to renderif no root or not set
	if (root == nullptr || !set) { return; }

	mat4 model(1.0f);
	model = translate(model, position);				//Horse position on the grid
	model = rotate(model, radians(yRot), yAxis);	//Yaw (side) rotation of the horse
	model = rotate(model, radians(zRot), zAxis);	//Pitch (vertical) rotation of the horse
	model = scale(model, vec3(size));				//Scale factor of the horse

	//Rendering setup
	glBindVertexArray(VAO);
	glLineWidth(3.0f);

	//Render starting at the root
	root->render(model);

	//Rendering end
	glLineWidth(1.0f);
	glBindVertexArray(0);
}

void Mesh::reset()
{
	position = start.position;
	size = start.size;
	yRot = start.yRot;
	zRot = start.zRot;
}
