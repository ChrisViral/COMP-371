#include "Cube.h"

using glm::vec3;
using std::vector;

Cube::Cube() : name(""), colour(vec3(0.0f)), position(vec3(0.0f)), scale(vec3(0.0f)), offset(vec3(0.0f)),
			   angle(0.0f), parent(nullptr), children(vector<Cube*>()) { }

Cube::~Cube()
{
	for (Cube* child : children)
	{
		delete child;
	}
	children.clear();
	parent = nullptr;
}
