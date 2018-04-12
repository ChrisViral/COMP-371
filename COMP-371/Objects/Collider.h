#pragma once
#include <glm/glm.hpp>

//Forward declarations
class Mesh;

/**
 * \brief Spherical collider implementation
 */
class Collider
{
public:
	//Constructors/destructors
	/**
	 * \brief Creates a new collider over the given mesh
	 * \param mesh Mesh to set the collider on
	 */
	explicit Collider(Mesh* mesh);
	/**
	 * \brief Copy constructor, copies the collider onto a given mesh
	 * \param collider Collider to copy 
	 * \param mesh     Mesh to apply the new collider to
	 */
	Collider(const Collider& collider, Mesh* mesh);
	/**
	 * \brief Destructor, frees allocated memory
	 */
	~Collider();

	//Setters
	/**
	 * \brief Sets the radius of the collider
	 * \param radius New radius
	 */
	void setRadius(const float radius) { this->radius = radius; }

	//Methods
	/**
	 * \brief Gets the central position of the collider according to the parent Mesh
	 * \return Position of the collider
	 */
	glm::vec3 getPosition() const;
	/**
	 * \brief Checks if this collider collides with another given collider
	 * \param other Collider to check collisions against
	 * \return True if they are colliding, false otherwise
	 */
	bool colliding(Collider* other) const;

private:
	//Fields
	Mesh* mesh;
	float radius;
};
