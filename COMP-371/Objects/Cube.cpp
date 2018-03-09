#include "Cube.h"

using glm::vec3;
using std::vector;

Cube::Cube() : pos(vec3(0.0f)), scale(vec3(0.0f)), offset(vec3(0.0f)), angle(0), parent(nullptr), children(vector<Cube*>()) { }

Cube::~Cube()
{
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
	children.clear();
	parent = nullptr;
}
