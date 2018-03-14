#include <glm/gtc/matrix_transform.hpp>
#include "Axis.h"
#include "../Globals.h"

using glm::radians;
using glm::vec3;
using glm::mat4;

const GLfloat Axis::vertices[] =
{
	//Position			Texture coord
	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, //First vertex
	1.0f, 0.0f, 0.0f,	0.0f, 0.0f  //Second vertex
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	//Setup the texture vertex attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Axis::render() const
{
	//Bunch of static values for this function
	static const float rot = radians(90.0f);
	static const vec3 offset(0.0f, 0.01f, 0.0f);
	static const vec3 red(1.0f, 0.0f, 0.0f);
	static const vec3 green(0.0f, 1.0f, 0.0f);
	static const vec3 blue(0.0f, 0.0f, 1.0f);

	//Bind VAO
	glBindVertexArray(VAO);

	//Set line width
	glLineWidth(5.0f);
	shader->setInt("state", 0);

	mat4 model(1.0f);
	model = translate(model, offset); //Slightly translate up to avoid clipping with the grid
	model = scale(model, vec3(length));

	//Render x axis
	shader->setMat4("MVP", vpMatrix * model); //No transformation required
	shader->setVec3("colour", red);			  //X axis is red
	glDrawArrays(GL_LINES, 0, 2);

	//Render y axis
	shader->setMat4("MVP", vpMatrix * rotate(model, rot, blue));	//Rotate vertically (90 degrees on Z axis)
	shader->setVec3("colour", green);										//Y axis is green
	glDrawArrays(GL_LINES, 0, 2);

	//Render z axis
	shader->setMat4("MVP", vpMatrix * rotate(model, -rot, green)); //Rotate horizontally (-90 degrees on y axis)
	shader->setVec3("colour", blue);										  //Z axis is blue
	glDrawArrays(GL_LINES, 0, 2);

	//Reset line width
	glLineWidth(1.0f);

	//Unbind VAO
	glBindVertexArray(0);
}