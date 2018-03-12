#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Mesh;

class Cube
{
public:
	explicit Cube(Mesh* mesh);
	~Cube();

	bool isRoot() const { return parent == nullptr; }
	Cube* getParent() const { return parent; }
	std::vector<Cube*> getChildren() const { return children; }

	void render(glm::mat4 model) const;

private:
	std::string name;
	glm::vec3 colour;
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 offset;
	float angle;
	Mesh* mesh;
	Cube* parent;
	std::vector<Cube*> children;

	friend class MeshParser;
};
