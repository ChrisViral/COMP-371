#pragma once
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

	const int size;
};
