// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"
#include "../Globals.h"
#include "Mesh.h"
#include "Shader.h"

#define CUBE_VERTICES 36

using glm::radians;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using std::vector;

Cube::Cube(Mesh* mesh) : name(""), colour(vec3(0.0f)), position(vec3(0.0f)), size(vec3(0.0f)), offset(vec3(0.0f)),
						 angle(0.0f), startAngle(0.0f), mesh(mesh), parent(nullptr), children(vector<Cube*>()) { }

Cube::Cube(const Cube& cube, Mesh* mesh) : name(cube.name), angle(cube.angle), startAngle(cube.startAngle), mesh(mesh), parent(nullptr)
{
	colour = vec3(cube.colour);
	position = vec3(cube.position);
	size = vec3(cube.size);
	offset = vec3(cube.offset);
	children = vector<Cube*>(cube.children.size());

	for (int i = 0; i < children.size(); i++)
	{
		Cube* c = new Cube(*cube.children[i], mesh);
		c->parent = this;
		children[i] = c;
	}
}

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
	//Get position matrix
	model = calculateModelMatrix(model);

	//Render
	if (!useTextures && shader == lightingShader) { shader->setVec3("colour", colour); }
	const mat4 m = scale(model, size); //Scale matrix
	shader->setMat4("model", m);
	glDrawElements(GL_TRIANGLES, CUBE_VERTICES, GL_UNSIGNED_INT, nullptr);

	//Render all children
	for (Cube* child : children)
	{
		child->render(model, shader);
	}
}

mat4 Cube::calculateModelMatrix(mat4 model) const
{
	//Joint rotation axis is always positive Z
	static const vec3 jointAxis(0.0f, 0.0f, 1.0f);

	//Position cube
	model = translate(model, position);
	model = rotate(model, radians(angle), jointAxis);
	model = translate(model, offset);
	return model;
}

void Cube::fillPoints(mat4 model, vector<vec3>& points)
{
	model = calculateModelMatrix(model);
	const mat4 m = scale(model, size);

	for (int i = 0; i < POINTS; i++)
	{
		const vec4 p = m * Mesh::points[i];
		points.push_back(vec3(p.x / p.w, p.y / p.w, p.z / p.w));
	}

	for (Cube* c : children)
	{
		c->fillPoints(model, points);
	}
}
