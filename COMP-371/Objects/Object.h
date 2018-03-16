// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"

/**
 * \brief Abstract object class for bodies being rendered
 */
class Object
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new Object with default values
	 */
	Object();
	/**
	 * \brief Frees up allocated memory
	 */
	virtual ~Object() = 0;

	/**
	* \brief Sets up all necessary objects for rendering
	*/
	virtual void setup() = 0;
	/**
	* \brief Renders the Object
	* \param shader Shader to use for rendering, a default shader will be selected if none is provided
	*/
	virtual void render(Shader* shader = nullptr) const = 0;

protected:
	//Constants
	static const glm::vec3 ambient;
	static const glm::vec3 diffuse;
	static const glm::vec3 specular;
	static const float shininess;

	//Fields
	GLuint VAO, VBO, EBO, tex;
	bool set;
};
