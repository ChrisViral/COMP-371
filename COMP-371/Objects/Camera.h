// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#pragma once

#include <glm/glm.hpp>

/**
 * \brief Target focused Camera implementation, implemented with view angle
 */
class Camera
{
public:
	//Constructors/Destructors
	/**
	* \brief Creates a new Camera, looking at the origin, positioned at a distance of 20u angled at 30degrees, on the Z axis
	*/
	Camera();
	/**
	* \brief Creates a Camera at the given distance and angle from the given target, with the given up vector
	* \param distance Distance from the origin in units
	* \param angle    Angle from the XZ plane
	* \param target   Target to point the camera at
	* \param up       Up vector of the camera
	*/
	explicit Camera(float distance, float angle, glm::vec3 target = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	/**
	 * \brief Destructor, frees the memory associated with the Camera
	 */
	~Camera();

	//Getters
	/**
	 * \brief World position of the Camera
	 * \return Position vector of the Camera
	 */
	glm::vec3 getPosition() const { return target + position; }

	//Methods
	/**
	 * \brief Gets the view Matrix associated with the current state of the camera
	 * \return The view Matrix
	 */
	glm::mat4 view() const;
	/**
	 * \brief Gets the perspective projection matrix associated with the current state of the Camera
	 * \return The perspective Matrix
	 */
	glm::mat4 perspective() const;
	/**
	 * \brief Adjusts the distance from the camera to the target by the amount d
	 * \param d Amount to adjust the distance by
	 */
	void adjustDistance(const float d);
	/**
	 * \brief Moves the camera target by the specified vector
	 * \param movement Movement to apply to the target
	 */
	void moveTarget(const glm::vec3 movement);
	/**
	 * \brief Tilts the camera vertically by the specified amount
	 * \param tilt Angle to tilt by, in degrees
	 */
	void tiltCamera(const float tilt);
	/**
	 * \brief Pans the camera horizontally by the specified amount
	 * \param pan Angle to pan by, in degrees
	 */
	void panCamera(const float pan);
	/**
	 * \brief Resets the Camera to it's original orientation
	 */
	void reset();

private:
	//Position vectors
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;

	//Original positions
	glm::vec3 origPos;
	glm::vec3 origTgt;
	float origTilt;

	//Angles
	float tiltAngle;
	float panAngle;

	//Private methods
	/**
	 * \brief Calculates the distance from the camera to the target
	 * \return Distance, in units
	 */
	float distance() const { return length(position); }
	/**
	 * \brief Updates the camera's position vector according to it's distance and view angles
	 */
	void updatePosition();
};