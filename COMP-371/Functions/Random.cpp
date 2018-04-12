#include <cstdlib>
#include "Random.h"

int randomRange(const int min, const int max)
{
	//Return a random value between min and max
	return (rand() % (max - min + 1)) + min;
}

float randomRangef(const float min, const float max)
{
	//Return a random value between min and max
	return (rand() / (static_cast<float>(RAND_MAX / (max - min)))) + min;
}

int randomSign()
{
	return rand() / static_cast<double>(RAND_MAX) > 0.5 ? 1 : -1;
}