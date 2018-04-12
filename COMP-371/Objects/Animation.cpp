#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>
#include "Animation.h"
#include "../Globals.h"
#include "Mesh.h"

using glm::min;
using glm::radians;
using glm::vec3;

Animation::Animation(Mesh* mesh) : mesh(mesh), state(WALKING), speed(1.0f), steps(5.0f), rotSpeed(45.0f), rotation(30.0f),
								   waitTime(1.0f), progress(0.0f) { }

Animation::Animation(const Animation& animation, Mesh* mesh) : mesh(mesh)
{
	state = animation.state;
	speed = animation.speed;
	steps = animation.steps;
	rotSpeed = animation.rotSpeed;
	rotation = animation.rotation;
	waitTime = animation.waitTime;
	progress = animation.progress;
}

Animation::~Animation() { }

void Animation::animate()
{
	static vec3 unit = vec3(1.0f, 0.0f, 0.0f);

	switch (state)
	{
		case WALKING:
		{
			const vec3 movement = normalize(rotateY(unit, radians(mesh->yRot)));
			float distance = deltaTime * speed;
			if (distance > steps - progress)
			{
				distance = steps - progress;
				state = TURNING;
				progress = 0.0f;
			}
			else { progress += distance; }

			mesh->position += movement * distance;
			break;
		}

		case TURNING:
		{
			float turn = deltaTime * rotSpeed;
			if (turn > rotation - progress)
			{
				turn = rotation - progress;
				state = WAITING;
				progress = 0.0f;
			}
			else { progress += turn; }

			//Clamp to 0-360
			mesh->yRot = fmod(mesh->yRot + turn, 360);
			break;
		}

		case WAITING:
		{
			const float wait = deltaTime;
			if (wait > waitTime - progress)
			{
				state = WALKING;
				progress = 0.0f;
			}
			else { progress += wait; }

			break;
		}
	}
}