#pragma once
#include <GL/glew.h>
#include "Object.h"

class Grid : public Object
{
public:
	explicit Grid(const int size);
	~Grid();

	void setup() override;
	void render() const override;

private:
	static const GLfloat vertices[];

	int size;
};
