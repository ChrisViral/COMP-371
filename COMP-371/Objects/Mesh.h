#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Cube.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

private:
	static GLfloat vertices[];
	static GLint indices[];

	Cube* root;
	glm::vec3 position;
	float scale;
	float xRot;
	float zRot;

	friend class MeshParser;
};
