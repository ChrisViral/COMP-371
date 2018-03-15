#include <glm/gtc/matrix_transform.hpp>
#include "Shadows.h"

#define FOV 160.0f
#define NEAR 0.5f
#define FAR 100.0f

using glm::lookAt;
using glm::perspective;
using glm::radians;
using glm::vec3;
using glm::mat4;

Shadows::Shadows() : Shadows(nullptr) { }

Shadows::Shadows(Light* light): light(nullptr), FBO(0), depthMap(0), set(false) { }

Shadows::~Shadows()
{
	if (set)
	{
		glDeleteFramebuffers(1, &FBO);
		glDeleteTextures(1, &depthMap);
	}
	light = nullptr;
}

void Shadows::setup()
{
	//Generate frame buffer
	glGenFramebuffers(1, &FBO);

	//Create shadow texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Bind to fram buffer
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	//Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

mat4 Shadows::view() const
{
	//Light look vectors
	static const vec3 center(0.0f);
	static const vec3 up(0.0f, 1.0f, 0.0f);
	return lookAt(light->getPosition(), center, up);
}

mat4 Shadows::projection() const
{
	return perspective(radians(FOV), static_cast<float>(SHADOW_WIDTH) / SHADOW_HEIGHT, NEAR, FAR);
}

