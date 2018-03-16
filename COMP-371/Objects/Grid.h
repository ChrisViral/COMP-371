// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#pragma once
#include "Object.h"

/**
 * \brief Planar world grid
 */
class Grid : public Object
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new Grid of the given size
	 * \param size Size of the grid from the center (total grid side length will be twice this)
	 */
	explicit Grid(const int size);
	/**
	 * \brief Frees up allocated memory
	 */
	~Grid();

	//Methods
	/**
	* \brief Sets up all necessary objects for rendering
	*/
	void setup() override;
	/**
	* \brief Renders the Grid
	* \param shader Shader to use for rendering, a lighting shader is used if none is provided
	*/
	void render(Shader* shader = nullptr) const override;

private:
	//Constants
	static const GLfloat vertices[];
	static const GLint indices[];
	static const GLint lineIndices[];
	static const glm::vec3 colour;

	//Fields
	const int size;
	GLuint lEBO;
};
