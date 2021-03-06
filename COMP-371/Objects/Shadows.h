// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#pragma once
#include <GL/glew.h>
#include "Light.h"

#define SHADOW_WIDTH 2048
#define SHADOW_HEIGHT 2048
#define SHADOWS_FAR_PLANE 100.0f

/**
 * \brief Two pass shadows implementation
 */
class Shadows
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new Shadows without a light source
	 */
	Shadows();
	/**
	 * \brief Creates a Shadows object with the given light source
	 * \param light Light source for the shadows
	 */
	explicit Shadows(Light* light);
	/**
	 * \brief Frees up allocated memory
	 */
	~Shadows();

	//Getters
	/**
	 * \brief Gets the FBO of this Shadows
	 * \return FBO address
	 */
	GLuint getFBO() const { return FBO; }
	/**
	 * \brief Gets the depth map of this Shadows
	 * \return Depth map address
	 */
	GLuint getCubeMap() const { return cubeMap; }

	//Methods
	/**
	* \brief Sets up all necessary objects for shadows rendering
	*/
	void setup();
	/**
	 * \brief Gets the views matrix from the light source
	 * \return View matrix
	 */
	std::vector<glm::mat4> views() const;
	/**
	 * \brief Gets the projection matrix from the light source
	 * \return Projection matrix
	 */
	glm::mat4 projection() const;

private:
	//Fields
	Light* light;
	GLuint FBO, cubeMap;
	bool set;
};
