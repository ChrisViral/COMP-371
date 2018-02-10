// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 1
// Feburary 8th 2018

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "../Globals.h"

//Camera constants
#define FOV 45.0f
#define PAN 0.0f
#define DISTANCE 5.0f
#define ANGLE 0.0f
#define NEAR_PLANE 0.01f
#define FAR_PLANE 200.0f
#define MIN_DISTANCE 1.0f
#define MAX_ANGLE 89.0f

using glm::vec3;
using glm::mat4;
using glm::radians;

Camera::Camera() : Camera(DISTANCE, ANGLE) { }

Camera::Camera(const float distance, const float angle, const vec3 target, const vec3 up) : position(vec3(distance, 0.0f, 0.0f)), target(target), up(normalize(up)), tiltAngle(angle), panAngle(PAN)
{
	//Initialize position vector
	updatePosition();

	//Setup original values
	origPos = position;
	origTgt = target;
	origTilt = angle;
	
}

Camera::~Camera() { }

mat4 Camera::view() const
{
	//Get view with lookAt
	return lookAt(position + target, target, up);
}

mat4 Camera::perspective() const
{
	//Generate perspective matrix
	return glm::perspective(radians(FOV), static_cast<float>(screenWidth) / screenHeight, NEAR_PLANE, FAR_PLANE);
}

void Camera::adjustDistance(const float d)
{
	//Get new ang old distance
	const float oldDistance = distance();
	const float newDistance = oldDistance + d;

	//If new distance too small, do not zoom in more
	if (newDistance <= MIN_DISTANCE) { return; }

	//Multiply vector by the distance ratio
	position *= newDistance / oldDistance;
}

void Camera::moveTarget(const vec3 movement)
{
	//Move the target by the given vector
	target += movement;
}

void Camera::tiltCamera(const float tilt)
{
	//Add additional tilt
	tiltAngle += tilt;

	//Check if within max angle bounds
	if (tiltAngle > MAX_ANGLE) { tiltAngle = MAX_ANGLE; }
	else if (tiltAngle < -MAX_ANGLE) { tiltAngle = -MAX_ANGLE; }

	//Update position vector
	updatePosition();
}

void Camera::panCamera(const float pan)
{
	//Add given pan and update position vector
	panAngle += pan;
	updatePosition();
}

void Camera::reset()
{
	//Reset all values to original values
	position = origPos;
	target = origTgt;
	tiltAngle = origTilt;
	panAngle = PAN;
}

void Camera::updatePosition()
{
	//Get distance, and update each component accordingly
	const float d = distance();
	position.x = cos(radians(tiltAngle)) * sin(radians(panAngle)) * d;
	position.y = sin(radians(tiltAngle)) * d;
	position.z = cos(radians(tiltAngle)) * cos(radians(panAngle)) * d;
}
