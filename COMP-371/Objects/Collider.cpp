#include "Collider.h"
#include "Mesh.h"

using glm::vec3;

Collider::Collider(Mesh* mesh) : mesh(mesh), radius(0.0f) { }

Collider::Collider(const Collider& collider, Mesh* mesh) : mesh(mesh), radius(collider.radius) { }

Collider::~Collider()
{
	mesh = nullptr;
}

vec3 Collider::getPosition() const
{
	return mesh->position;
}

bool Collider::colliding(Collider* other) const
{
	//The spheres intersect if the distance between them is less than the sum of their radii
	return length(getPosition() - other->getPosition()) < radius + other->radius;
}
