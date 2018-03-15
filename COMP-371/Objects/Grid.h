#pragma once
#include "Object.h"

class Grid : public Object
{
public:
	explicit Grid(const int size);
	~Grid();

	void setup() override;
	void render(Shader* shader = nullptr) const override;

private:
	static const GLfloat vertices[];
	static const GLint indices[];
	static const GLint lineIndices[];
	static const glm::vec3 colour;

	const int size;
	GLuint lEBO;
};
