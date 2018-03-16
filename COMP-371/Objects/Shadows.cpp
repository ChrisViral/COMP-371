#include <glm/gtc/matrix_transform.hpp>
#include "Shadows.h"
#include "../Globals.h"

#define FOV 150.0f
#define NEAR 0.5f
#define FAR 200.0f

using glm::lookAt;
using glm::perspective;
using glm::radians;
using glm::vec3;
using glm::mat4;

Shadows::Shadows() : Shadows(nullptr) { }

Shadows::Shadows(Light* light): light(light), FBO(0), depthMap(0), set(false) { }

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
	if (!set)
	{
		//Generate frame buffer
		glGenFramebuffers(1, &FBO);

		//Create shadow texture
		static const float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);

		//Bind to fram buffer
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		//Set texture
		lightingShader->use();
		lightingShader->setInt("shadowMap", 2);

		//Unbind
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Raise set flag
		set = true;
	}
}

mat4 Shadows::view() const
{
	//Light look vectors
	static const vec3 target(0.0f, 0.0f, 0.0f);
	static const vec3 up(0.0f, 0.0f, -1.0f);
	return lookAt(light->getPosition(), target, up);
}

mat4 Shadows::projection() const
{
	//return glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 100.0f);
	return perspective(radians(FOV), static_cast<float>(SHADOW_WIDTH) / SHADOW_HEIGHT, NEAR, FAR);
}

