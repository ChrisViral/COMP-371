// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

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
	//Return -1 or 1 depending on random generation
	return rand() / static_cast<double>(RAND_MAX) > 0.5 ? 1 : -1;
}