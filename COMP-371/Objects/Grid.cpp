#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Grid.h"
#include "../Globals.h"

#define GRID_VERTICES 6
#define LINE_INDICES 8
#define TEXTURE_PATH "Textures/grass.png"

using glm::radians;
using glm::vec3;
using glm::mat4;
using std::cout;
using std::endl;

const GLfloat Grid::vertices[] =
{
	//Position			Normal				Texture
	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,0.0f,	0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,0.0f,	1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,	0.0f, 1.0f,0.0f,	1.0f, 1.0f,
	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,0.0f,	0.0f, 1.0f
};

const GLint Grid::indices[] =
{
	0, 1, 2,
	0, 2, 3
};

const GLint Grid::lineIndices[] =
{
	0, 1,
	1, 2,
	2, 3,
	3, 4
};

const vec3 Grid::colour = vec3(1.0f);

Grid::Grid(const int size) : Object(), size(size), lEBO(0) { }

Grid::~Grid()
{
	if (set)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &lEBO);
		glDeleteTextures(1, &tex);
	}
}

void Grid::setup()
{
	if (!set)
	{
		//Generate containers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &lEBO);

		//Bind VAO
		glBindVertexArray(VAO);

		//Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//Bind lEBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineIndices), lineIndices, GL_STATIC_DRAW);

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

		lightingShader->setInt("tex1", 0);

		//Unbind
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		set = true;
	}
}

void Grid::render(Shader* shader) const
{
	static const vec3 ambient(0.05f, 0.15f, 0.05f);
	static const vec3 diffuse(0.4f, 0.5f, 0.4f);
	static const vec3 specular(0.05f, 0.7f, 0.05f);
	static const float shininess = 13.0f;

	//Don't render if not correctly setup
	if (!set || size <= 0) { return; }

	//Bind VAO
	glBindVertexArray(VAO);

	const GLenum renderMode = useTextures ? GL_TRIANGLES : GL_LINES;
	if (shader == nullptr)
	{
		shader = lightingShader;
		shader->use();
		shader->setMat4("vpMat", vpMatrix);
		shader->setVec3("cameraPosition", camera->getPosition());

		if (useTextures)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			shader->setInt("state", 1);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex);
			shader->setVec3("material.ambient", ambient);
			shader->setVec3("material.diffuse", diffuse);
			shader->setVec3("material.specular", specular);
			shader->setFloat("material.shininess", shininess);
		}
		else
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lEBO);
			shader->setInt("state", 0);
			shader->setVec3("colour", colour);
			shader->setVec3("material.ambient", Object::ambient);
			shader->setVec3("material.diffuse", Object::diffuse);
			shader->setVec3("material.specular", Object::specular);
			shader->setFloat("material.shininess", Object::shininess);
		}
	}
	
	const mat4 m(1.0f);
	for (int i = -size; i < size; i++)
	{
		for (int j = -size; j < size; j++)
		{
			shader->setMat4("model", translate(m, vec3(i, 0.0f, j)));
			glDrawElements(renderMode, GRID_VERTICES, GL_UNSIGNED_INT, nullptr);
		}
	}

	//Unbind VAO
	glBindVertexArray(0);
}
