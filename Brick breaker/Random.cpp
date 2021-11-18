#include "Random.h"

#include <random>

float Random::random(float max) {
	return random(0, max);
}

float Random::random(float min, float max) {
	float r = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return r;
}