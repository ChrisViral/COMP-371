#pragma once
#include "Object.h"

class Axis : public Object
{
public:
	explicit Axis(const int length);
	~Axis();

	void setup() override;
	void render(Shader* shader = nullptr) const override;

private:
	static const GLfloat vertices[];

	const int length;
};
