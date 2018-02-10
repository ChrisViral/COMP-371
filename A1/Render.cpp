// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 1
// Feburary 8th 2018

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.h"
#include "Render.h"

//Cube constants
#define CUBE_AMOUNT 11
#define CUBE_VERTICES 36
#define GRID_SIZE 50

using glm::vec3;
using glm::mat4;
using glm::radians;

//Setup render offsets original values
vec3 offset(0.0f);
float size = 1.0f;
float yawAngle = 0.0f;
float pitchAngle = 0.0f;

//Horse cubes colours
vec3 horseColours[] =
{
	vec3(0.7f), //Torso

	vec3(0.4f), //Upper legs
	vec3(0.4f),
	vec3(0.4f),
	vec3(0.4f),

	vec3(0.3f), //Lower legs
	vec3(0.3f),
	vec3(0.3f),
	vec3(0.3f),

	vec3(0.6f), //Neck

	vec3(0.5f)  //Head
};

//Horse cubes positions
vec3 horsePositions[] =
{
	vec3(0.0f, 2.0f, 0.0f),    //Torso

	vec3(1.1f, 1.3f,  0.3f),  //Upper legs
	vec3(1.1f, 1.3f, -0.3f),
	vec3(-1.1f, 1.3f,  0.3f),
	vec3(-1.1f, 1.3f, -0.3f),

	vec3(1.1f, 0.45f,  0.3f), //Lower legs
	vec3(1.1f, 0.45f, -0.3f),
	vec3(-1.1f, 0.45f,  0.3f),
	vec3(-1.1f, 0.45f, -0.3f),

	vec3(1.3f, 2.2f, 0.0f),    //Neck

	vec3(2.3f, 2.2f, 0.0f)     //Head
};

//Horse cubes sizes
vec3 horseSizes[] =
{
	vec3(2.5f, 1.0f, 0.8f),   //Torso

	vec3(0.24f, 0.8f, 0.19f), //Upper legs
	vec3(0.24f, 0.8f, 0.19f),
	vec3(0.24f, 0.8f, 0.19f),
	vec3(0.24f, 0.8f, 0.19f),

	vec3(0.28f, 0.9f, 0.23f), //Lower legs
	vec3(0.28f, 0.9f, 0.23f),
	vec3(0.24f, 0.9f, 0.19f),
	vec3(0.24f, 0.9f, 0.19f),

	vec3(1.7f, 0.6f, 0.4f),   //Neck

	vec3(1.1f, 0.4f, 0.3f)    //Head
};

//Horse cubes Z axis rotation
float horseRotations[] =
{
	 0.0f,  //Torso

	 0.0f,  //Upper legs
	 0.0f,
	 0.0f,
	 0.0f,

	 0.0f,  //Lower legs
	 0.0f,
	 0.0f,
	 0.0f,

	 30.0f, //Neck

	-65.0f  //Head
};

void setupCubes()
{
	//Cube info - a unit cube (all edges of size 1) centered at the world origin
	GLfloat cubeVertices[] =
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

	//Cube triangles indices
	GLint cubeIndices[] =
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

	//Generate containers
	glGenVertexArrays(1, &cubesVAO);
	glGenBuffers(1, &cubesVBO);
	glGenBuffers(1, &cubesEBO);

	//Bind VAO
	glBindVertexArray(cubesVAO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, cubesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	//Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubesEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	//Setup the position vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void setupLines()
{
	//Vertices for a length 100 unit length line on the X axis, centered on the world origin
	GLfloat linesVertices[] =
	{
		-50.0f,  0.0f, 0.0f, //First vertex
		 50.0f,  0.0f, 0.0f, //Second vertex
	};

	//Generate containers
	glGenVertexArrays(1, &linesVAO);
	glGenBuffers(1, &linesVBO);

	//Bind VAO
	glBindVertexArray(linesVAO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, linesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linesVertices), linesVertices, GL_STATIC_DRAW);

	//Setup the position vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void setupAxis()
{
	//Line of 5 units length, starting at the origin, on the X axis
	GLfloat axisVertices[] =
	{
		0.0f,  0.0f, 0.0f, //First vertex
		5.0f,  0.0f, 0.0f, //Second vertex
	};

	//Generate containers
	glGenVertexArrays(1, &axisVAO);
	glGenBuffers(1, &axisVBO);

	//Bind VAO
	glBindVertexArray(axisVAO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

	//Setup the position vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void renderCubes()
{
	//Bind VAO
	glBindVertexArray(cubesVAO);

	//Set line width (for line rendering)
	glLineWidth(3.0f);

	//Rotation axises
	const vec3 yAxis(0.0f, 1.0f, 0.0f), zAxis(0.0f, 0.0f, 1.0f);

	//Loopt through all the cubes to render
	for (int i = 0; i < CUBE_AMOUNT; i++)
	{
		//Set shader colour
		shader.setVec3("colour", horseColours[i]);

		//User set offsets
		mat4 model(1.0f);
		model = translate(model, offset);					//Horse position on the grid
		model = rotate(model, radians(yawAngle), yAxis);	//Yaw (side) rotation of the horse
		model = rotate(model, radians(pitchAngle), zAxis);	//Pitch (vertical) rotation of the horse
		model = scale(model, vec3(size));					//Scale factor of the horse

		//Model assembly
		model = translate(model, horsePositions[i]);				//Position of the cube on the horse
		model = rotate(model, radians(horseRotations[i]), zAxis);	//Rotation of the cube relative to the horse
		model = scale(model, horseSizes[i]);						//Size of the cube relative to the horse

		//Set model matrix
		shader.setMat4("MVP", vpMatrix * model);

		//Render the horse
		glDrawElements(GL_TRIANGLES, CUBE_VERTICES, GL_UNSIGNED_INT, nullptr);
	}

	//Reset line width
	glLineWidth(1.0f);

	//Unbin VAO
	glBindVertexArray(0);
}

void renderLines()
{
	//Bind VAO
	glBindVertexArray(linesVAO);

	//Set grid lines to white
	shader.setVec3("colour", vec3(1.0f));

	//Render lines on the x axis
	for (int i = -GRID_SIZE; i <= GRID_SIZE; i++)
	{
		shader.setMat4("MVP", translate(vpMatrix, vec3(0.0f, 0.0f, i)));
		glDrawArrays(GL_LINES, 0, 2);
	}

	//Rotate base matrix 90 degrees on the Y axis
	const mat4 model = rotate(vpMatrix, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));

	//Render the lines on the y axis
	for (int i = -GRID_SIZE; i <= GRID_SIZE; i++)
	{
		shader.setMat4("MVP", translate(model, vec3(0.0f, 0.0f, i)));
		glDrawArrays(GL_LINES, 0, 2);
	}

	//Unbind VAO
	glBindVertexArray(0);
}

void renderAxis()
{
	//Bind VAO
	glBindVertexArray(axisVAO);

	//Set line width
	glLineWidth(5.0f);

	//Render x axis
	shader.setMat4("MVP", vpMatrix);					//No transformation required
	shader.setVec3("colour", vec3(1.0f, 0.0f, 0.0f));	//X axis is red
	glDrawArrays(GL_LINES, 0, 2);

	//Render y axis
	shader.setMat4("MVP", rotate(vpMatrix, radians(90.0f), vec3(0.0f, 0.0f, 1.0f)));	//Rotate vertically (90 degrees on Z axis)
	shader.setVec3("colour", vec3(0.0f, 1.0f, 0.0f));									//Y axis is green
	glDrawArrays(GL_LINES, 0, 2);

	//Render z axis
	shader.setMat4("MVP", rotate(vpMatrix, radians(-90.0f), vec3(0.0f, 1.0f, 0.0f)));	//Rotate horizontally (-90 degrees on y axis)
	shader.setVec3("colour", vec3(0.0f, 0.0f, 1.0f));								    //Z axis is bluew
	glDrawArrays(GL_LINES, 0, 2);

	//Reset line width
	glLineWidth(1.0f);

	//Unbind VAO
	glBindVertexArray(0);
}