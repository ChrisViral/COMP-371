#include <glm/gtc/matrix_transform.hpp>
#include "Grid.h"
#include "../Globals.h"

using glm::radians;
using glm::vec3;
using glm::mat4;

//Vertices for a length 100 unit length line on the X axis, centered on the world origin
const GLfloat Grid::vertices[] =
{
	-1.0f,  0.0f, 0.0f, //First vertex
	 1.0f,  0.0f, 0.0f, //Second vertex
};

Grid::Grid(const int size) : Object(), size(size) { }

Grid::~Grid()
{
	if (set)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}

void Grid::setup()
{
	if (!set)
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

		set = true;
	}
}

void Grid::render() const
{
	//Don't render if not correctly setup
	if (!set) { return; }

	//Bind VAO
	glBindVertexArray(VAO);

	//Set grid lines to white
	shader->setVec3("colour", vec3(1.0f));

	mat4 base(1.0f), model;
	//Render lines on the x axis
	for (int i = -size; i <= size; i++)
	{
		model = translate(base, vec3(0.0f, 0.0f, i));
		model = scale(model, vec3(size));
		shader->setMat4("MVP", vpMatrix * model);
		glDrawArrays(GL_LINES, 0, 2);
	}

	//Rotate base matrix 90 degrees on the Y axis
	base = rotate(base, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));

	//Render the lines on the y axis
	for (int i = -size; i <= size; i++)
	{
		model = translate(base, vec3(0.0f, 0.0f, i));
		model = scale(model, vec3(size));
		shader->setMat4("MVP", vpMatrix * model);
		glDrawArrays(GL_LINES, 0, 2);
	}

	//Unbind VAO
	glBindVertexArray(0);
}
