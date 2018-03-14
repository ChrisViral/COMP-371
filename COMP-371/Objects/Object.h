#pragma once
#include <GL/glew.h>

class Object
{
public:
	Object();
	virtual ~Object() = 0;

	virtual void setup() = 0;
	virtual void render() const = 0;

protected:
	GLuint VAO, VBO, EBO, tex;
	bool set;
};
