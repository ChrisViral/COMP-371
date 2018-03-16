// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#include <glm/gtx/transform.hpp>
#include "../Globals.h"
#include "Light.h"

//Light attributes
#define AMBIENT glm::vec3(0.3f)
#define DIFFUSE glm::vec3(1.0f)
#define SPECULAR glm::vec3(1.0f)
#define VERTEX_NUMBER 1

using glm::mat4;

const GLfloat Light::vertices[] =
{
	//Position			Colour
	0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f
};

Light::Light(const glm::vec3 position) : Object(), position(position) { }

Light::~Light()
{
	//Frees up buffers
	if (set)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}

void Light::setup()
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
		glEnableVertexAttribArray(0);

		//Setup the texture vertex attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//Set shader attributes
		lightingShader->setVec3("light.position", position);
		lightingShader->setVec3("light.ambient", AMBIENT);
		lightingShader->setVec3("light.diffuse", DIFFUSE);
		lightingShader->setVec3("light.specular", SPECULAR);
		set = true;
	}
}

void Light::render(Shader* shader) const
{
	//Get shader if none provided
	if (shader == nullptr)
	{
		shader = simpleShader;
		shader->use();
		shader->setMat4("vpMat", vpMatrix);
	}
	//Bind VAO
	glBindVertexArray(VAO);

	//Render
	shader->setMat4("model", translate(mat4(1.0f), position));
	glDrawArrays(GL_POINTS, 0, VERTEX_NUMBER);

	//Unbind VAO
	glBindVertexArray(0);
}
