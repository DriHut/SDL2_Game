#pragma once

#include <SDL.h>
#include "Ball.h"

class Block {
private :
	SDL_Rect collision_box;
	int level;
public:
	Block(int x, int y, int w, int h, int level);
	~Block();

	void render(SDL_Renderer* renderer);

	bool collision(Ball* ball);

	int collide(int pos_x, int pos_y, int radius);

	int getLevel() { return level; };
};