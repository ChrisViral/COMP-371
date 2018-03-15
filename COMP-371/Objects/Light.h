#pragma once
#include "Object.h"
#include <glm/detail/type_vec3.hpp>

class Light : public Object
{
public:
	explicit Light(const glm:: vec3 position);
	~Light();

	glm::vec3 getPosition() const { return position; }

	void setup() override;
	void render(Shader* shader = nullptr) const override;

private:
	static const GLfloat vertices[];

	glm::vec3 position;
};
