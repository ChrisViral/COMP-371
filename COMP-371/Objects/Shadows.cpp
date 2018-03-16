// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shadows.h"
#include "../Globals.h"

#define FOV 90.0f
#define NEAR 1.0f

using glm::lookAt;
using glm::perspective;
using glm::radians;
using glm::vec3;
using glm::mat4;
using std::vector;

Shadows::Shadows() : Shadows(nullptr) { }

Shadows::Shadows(Light* light) : light(light), FBO(0), cubeMap(0), set(false) { }

Shadows::~Shadows()
{
	//Free up memory when set
	if (set)
	{
		glDeleteFramebuffers(1, &FBO);
		glDeleteTextures(1, &cubeMap);
	}
	//Clear dangling pointers
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
		glGenTextures(1, &cubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
		for (int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, border);
		}


		//Bind to fram buffer
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, cubeMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Set texture
		lightingShader->use();
		lightingShader->setInt("shadowMap", 2);

		//Unbind
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Raise set flag
		set = true;
	}
}

vector<mat4> Shadows::views() const
{
	//Light look vectors
	static const vec3 x(1.0f, 0.0f, 0.0f);
	static const vec3 y(0.0f, 1.0f, 0.0f);
	static const vec3 z(0.0f, 0.0f, 1.0f);

	//Lookat matrix
	const vec3 pos = light->getPosition();
	vector<mat4> matrices;
	matrices.push_back(lookAt(pos, pos + x, -y));
	matrices.push_back(lookAt(pos, pos - x, -y));
	matrices.push_back(lookAt(pos, pos + y,  z));
	matrices.push_back(lookAt(pos, pos - y, -z));
	matrices.push_back(lookAt(pos, pos + z, -y));
	matrices.push_back(lookAt(pos, pos - z, -y));
	return matrices;
}

mat4 Shadows::projection() const
{
	//Point light means a perspective matrix
	return perspective(radians(FOV), static_cast<float>(SHADOW_WIDTH) / SHADOW_HEIGHT, NEAR, SHADOWS_FAR_PLANE);
}