#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Object
{
public:
	Object();
	virtual ~Object() = 0;

	virtual void setup() = 0;
	virtual void render() const = 0;

protected:
	static const glm::vec3 ambient;
	static const glm::vec3 diffuse;
	static const glm::vec3 specular;
	static const float shininess;

	GLuint VAO, VBO, EBO, tex;
	bool set;
};
