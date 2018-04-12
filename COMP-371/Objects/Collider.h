#pragma once
#include <glm/glm.hpp>

class Collider
{
public:
	explicit Collider(glm::vec3 position);
	Collider(const Collider& other);
	~Collider();

	void setPosition(const glm::vec3 position) { this->position = position; }
	void setRadius(const float radius) { this->radius = radius; }

	bool colliding(Collider* other) const;

private:
	glm::vec3 position;
	float radius;
};