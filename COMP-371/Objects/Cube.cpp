// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"
#include "../Globals.h"
#include "Mesh.h"
#include "Shader.h"

#define CUBE_VERTICES 36

using glm::radians;
using glm::vec3;
using glm::mat4;
using std::vector;

Cube::Cube(Mesh* mesh) : name(""), colour(vec3(0.0f)), position(vec3(0.0f)), size(vec3(0.0f)), offset(vec3(0.0f)),
						 angle(0.0f), startAngle(0.0f), mesh(mesh), parent(nullptr), children(vector<Cube*>()) { }

Cube::~Cube()
{
	//Delete all children
	for (Cube* child : children)
	{
		delete child;
	}
	//Remove dangling pointers
	children.clear();
	parent = nullptr;
	mesh = nullptr;
}

void Cube::render(mat4 model, Shader* shader) const
{
	//Joint rotation axis is always positive Z
	static const vec3 jointAxis(0.0f, 0.0f, 1.0f);

	//Position cube
	model = translate(model, position);
	model = rotate(model, radians(angle), jointAxis);
	model = translate(model, offset);

	//Render
	if (!useTextures && shader == lightingShader) { shader->setVec3("colour", colour); }
	shader->setMat4("model", scale(model, size));
	glDrawElements(GL_TRIANGLES, CUBE_VERTICES, GL_UNSIGNED_INT, nullptr);

	//Render all children
	for (Cube* child : children)
	{
		child->render(model, shader);
	}
}
