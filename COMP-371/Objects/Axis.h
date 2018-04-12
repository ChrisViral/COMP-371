// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#pragma once
#include "Object.h"

/**
 * \brief Set of X, Y, and Z axis
 */
class Axis : public Object
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new Axis set of the given length
	 * \param length Length of the axis lines
	 */
	explicit Axis(const int length);
	/**
	 * \brief Frees allocated memory
	 */
	~Axis();

	//Methods
	/**
	 * \brief Sets up all necessary objects for rendering
	 */
	void setup() override;
	/**
	 * \brief Renders the Axis
	 * \param shader Shader to use for rendering, a simple shader is used if none is provided
	 */
	void render(Shader* shader = nullptr) const override;

private:
	//Constants
	/// \brief Vertices of the axis
	static const GLfloat vertices[];

	//Fields
	///\brief Length of the axis
	const int length;
};
