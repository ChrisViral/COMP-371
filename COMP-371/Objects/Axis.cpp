#include <glm/gtc/matrix_transform.hpp>
#include "Axis.h"
#include "../Globals.h"

using glm::radians;
using glm::vec3;
using glm::mat4;

const GLfloat Axis::vertices[] =
{
	0.0f,  0.0f, 0.0f, //First vertex
	1.0f,  0.0f, 0.0f, //Second vertex
};

Axis::Axis(const int length) : Object(), length(length) { }

Axis::~Axis()
{
	if (set)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}

void Axis::setup()
{
	//Generate containers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind VAO
	glBindVertexArray(VAO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Setup the position vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Axis::render() const
{
	//Bind VAO
	glBindVertexArray(VAO);

	//Set line width
	glLineWidth(5.0f);

	mat4 model(1.0f);
	model = scale(model, vec3(length));

	//Render x axis
	shader->setMat4("MVP", vpMatrix * model);			//No transformation required
	shader->setVec3("colour", vec3(1.0f, 0.0f, 0.0f));	//X axis is red
	glDrawArrays(GL_LINES, 0, 2);

	//Render y axis
	shader->setMat4("MVP", vpMatrix * rotate(model, radians(90.0f), vec3(0.0f, 0.0f, 1.0f)));	//Rotate vertically (90 degrees on Z axis)
	shader->setVec3("colour", vec3(0.0f, 1.0f, 0.0f));											//Y axis is green
	glDrawArrays(GL_LINES, 0, 2);

	//Render z axis
	shader->setMat4("MVP", vpMatrix * rotate(model, radians(-90.0f), vec3(0.0f, 1.0f, 0.0f)));	//Rotate horizontally (-90 degrees on y axis)
	shader->setVec3("colour", vec3(0.0f, 0.0f, 1.0f));											//Z axis is blue
	glDrawArrays(GL_LINES, 0, 2);

	//Reset line width
	glLineWidth(1.0f);

	//Unbind VAO
	glBindVertexArray(0);
}

