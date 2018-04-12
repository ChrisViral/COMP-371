#include "Collider.h"

using glm::vec3;

Collider::Collider(const vec3 position) : position(position), radius(1.0f) { }

Collider::Collider(const Collider& collider) : radius(collider.radius)
{
	position = vec3(collider.position);
}

Collider::~Collider() { }

bool Collider::colliding(Collider* other) const
{
	//The spheres intersect if the distance between them is less than the sum of their radii
	return length(position - other->position) < radius + other->radius;
}