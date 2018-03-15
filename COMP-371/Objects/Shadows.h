#pragma once
#include <GL/glew.h>
#include "Light.h"

#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

class Shadows
{
public:
	Shadows();
	explicit Shadows(Light* light);
	~Shadows();

	GLuint getFBO() const { return FBO; }
	GLuint getDepthMap() const { return depthMap; }

	void setup();
	glm::mat4 view() const;
	glm::mat4 projection() const;

private:
	Light* light;
	GLuint FBO, depthMap;
	bool set;
};
