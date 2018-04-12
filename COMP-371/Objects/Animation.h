#pragma once

class Mesh;

enum State
{
	WALKING,
	TURNING,
	WAITING
};

class Animation
{
public:

	explicit Animation(Mesh* mesh);
	Animation(const Animation& animation, Mesh* mesh);
	~Animation();

	void animate();

private:
	Mesh* mesh;
	State state;
	float speed;
	float steps;
	float rotSpeed;
	float rotation;
	float waitTime;
	float progress;
};
