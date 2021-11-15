#include "Block.h"
#include "Colors.h"

Block::Block(int x, int y, int w, int h, int level) {
	collision_box.x = x;
	collision_box.y = y;
	collision_box.w = w;
	collision_box.h = h;
	this->level = level;
};

Block::~Block() {};

void Block::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, colors[level].r, colors[level].g, colors[level].b, colors[level].a);
	SDL_RenderFillRect(renderer, &collision_box);
}

bool Block::collision(Ball* ball) {
	int collision = collide(ball->getX(), ball->getY(), ball->getRadius());
	if (collision != 0) {
		ball->bounce(collision - 1);
		level--;
		return true;
	}
	return false;
}