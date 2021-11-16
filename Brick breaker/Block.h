#pragma once

#include "Collidable.h"

class Block : public Collidable {
private :
	int level;
public:
	Block(int x, int y, int w, int h, int level);
	~Block();

	void render(SDL_Renderer* renderer);

	bool collision(Ball* ball);

	int getLevel() { return level; };
};