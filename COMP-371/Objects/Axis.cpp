// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#include <glm/gtc/matrix_transform.hpp>
#include "Axis.h"
#include "../Globals.h"

#define VERTEX_NUMBER 6

using glm::radians;
using glm::vec3;
using glm::mat4;

const GLfloat Axis::vertices[] =
{
	//X axis			Colour
	0.0f, 0.02f, 0.0f,	1.0f, 0.0f, 0.0f, //First vertex
	1.0f, 0.02f, 0.0f,	1.0f, 0.0f, 0.0f, //Second vertex

	//Y axis			Colour
	0.0f, 0.02f, 0.0f,	0.0f, 1.0f, 0.0f, //First vertex
	0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f, //Second vertex

	//Z axis			Colour
	0.0f, 0.02f, 0.0f,	0.0f, 0.0f, 1.0f, //First vertex
	0.0f, 0.02f, 1.0f,	0.0f, 0.0f, 1.0f  //Second vertex
};

Axis::Axis(const int length) : Object(), length(length) { }

Axis::~Axis()
{
	//Get rid of buffers
	if (set)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}

void Axis::setup()
{
	//Do not generate more than once per lifetime
	if (!set)
	{
		//This VAO/VBO/EBO setup is adapted from https://learnopengl.com/Getting-started/Hello-Triangle

		//Generate containers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		//Bind VAO
		glBindVertexArray(VAO);

		//Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Setup the position vertex attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		glEnableVertexAttribArray(0);

		//Setup the texture vertex attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		set = true;
	}
}

void Axis::render(Shader* shader) const
{
	//Do not render until set
	if (!set) { return; }

	//Get shader if none provided
	if (shader == nullptr)
	{
		shader = simpleShader;
		shader->use();
		shader->setMat4("vpMat", vpMatrix);
	}
	//Bind VAO
	glBindVertexArray(VAO);

	//Set line width
	glLineWidth(5.0f);
	shader->setMat4("model", scale(mat4(1.0f), vec3(length)));
	glDrawArrays(GL_LINES, 0, VERTEX_NUMBER);

	//Reset line width
	glLineWidth(1.0f);

	//Unbind VAO
	glBindVertexArray(0);
}