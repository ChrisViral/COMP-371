#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>
#include <vector>
#include "Animation.h"
#include "../Globals.h"
#include "Mesh.h"
#include "../COMP-371.h"

using glm::radians;
using glm::vec3;
using std::vector;

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
			vec3 movement = normalize(rotateY(unit, radians(mesh->yRot)));
			float distance = deltaTime * speed;
			const float p = steps - progress;
			if (distance > p)
			{
				distance = p;
				state = TURNING;
				progress = 0.0f;
			}
			else { progress += distance; }

			movement *= distance;
			mesh->position += movement;
			/*
			//Get potential collisions
			int index = -1;
			vector<int> potential;
			for (int i = 0; i < HORSE_COUNT; i++)
			{
				//Current horse
				Mesh* h = hord[i];
				if (h == mesh) { index = i; }
				else
				{
					//Test if within 8 units
					if (length(mesh->position - h->position) < 8.0f)
					{
						potential.push_back(i);
					}
				}
			}

			//Test each potential collision
			for (int i : potential)
			{
				Mesh* h = hord[i];
				if (mesh->collider->colliding(h->collider))
				{
					//If colliding, roll back forward movement
					mesh->position -= movement;
					//If indexed first, rotate, else wait for collision resolution
					if (index < i)
					{
						mesh->yRot = fmod(mesh->yRot + deltaTime * rotSpeed, 360.0f);
					}
				}
			}
			*/
			break;
		}

		case TURNING:
		{
			float turn = deltaTime * rotSpeed;
			const float p = rotation - progress;
			if (abs(turn) > p)
			{
				turn = turn < 0 ? -p : p;
				state = WAITING;
				progress = 0.0f;
			}
			else { progress += abs(turn); }

			//Clamp to 0-360
			mesh->yRot = fmod(mesh->yRot + turn, 360.0f);
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