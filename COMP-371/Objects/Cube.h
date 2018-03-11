#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Cube
{
public:
	Cube();
	~Cube();

	Cube* getParent() const { return parent; }
	std::vector<Cube*> getChildren() const { return children; }

private:
	std::string name;
	glm::vec3 colour;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 offset;
	float angle;
	Cube* parent;
	std::vector<Cube*> children;

	friend class MeshParser;
};