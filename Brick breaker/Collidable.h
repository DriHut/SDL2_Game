#pragma once

#include <SDL.h>
#include "Ball.h"

class Collidable {
protected:
	SDL_Rect collision_box;
public:
	Collidable(int x = 0, int y = 0, int w = 0, int h = 0);
	~Collidable();

	bool collision(Ball* ball);

	int collide(int pos_x, int pos_y, int radius);
};