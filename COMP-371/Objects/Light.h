// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#pragma once
#include "Object.h"
#include <glm/detail/type_vec3.hpp>

/**
 * \brief Point light source
 */
class Light : public Object
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new Light at the given position
	 * \param position Position of the light
	 */
	explicit Light(const glm:: vec3 position);
	/**
	 * \brief Frees up assigned memory
	 */
	~Light();

	//Getters
	/**
	 * \brief Gets the position of the light
	 * \return World position of the light
	 */
	glm::vec3 getPosition() const { return position; }

	//Methods
	/**
	* \brief Sets up all necessary objects for rendering
	*/
	void setup() override;
	/**
	* \brief Renders the Light
	* \param shader Shader to use for rendering, a simple shader is used if none is provided
	*/
	void render(Shader* shader = nullptr) const override;

private:
	//Constants
	static const GLfloat vertices[];

	//Fields
	glm::vec3 position;
};
