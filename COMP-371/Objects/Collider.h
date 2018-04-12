#pragma once
#include <glm/glm.hpp>

class Mesh;

class Collider
{
public:
	explicit Collider(Mesh* mesh);
	Collider(const Collider& other, Mesh* mesh);
	~Collider();

	void setRadius(const float radius) { this->radius = radius; }

	glm::vec3 getPosition() const;
	bool colliding(Collider* other) const;

private:
	Mesh* mesh;
	float radius;
};
