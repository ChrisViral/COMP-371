#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class Mesh;
class Shader;

class Cube
{
public:
	explicit Cube(Mesh* mesh);
	~Cube();

	bool isRoot() const { return parent == nullptr; }
	std::string getName() const { return name; }
	Cube* getParent() const { return parent; }
	std::vector<Cube*> getChildren() const { return children; }

	void render(glm::mat4 model, Shader* shader) const;

private:
	std::string name;
	glm::vec3 colour;
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 offset;
	float angle, startAngle;
	Mesh* mesh;
	Cube* parent;
	std::vector<Cube*> children;

	friend class MeshParser;
	///\brief Set input callback function as friend
	friend void key_callback(GLFWwindow*, int, int, int, int);
};
