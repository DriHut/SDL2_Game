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

int Block::collide(int pos_x, int pos_y, int radius) {

	// temporary variables to set edges for testing
	int testX = pos_x;
	int testY = pos_y;

	// which edge is closest?
	if (pos_x < collision_box.x)                testX = collision_box.x;                           // test left edge
	else if (pos_x > collision_box.x + collision_box.w) testX = collision_box.x + collision_box.w; // right edge
	if (pos_y < collision_box.y)                testY = collision_box.y;                           // top edge
	else if (pos_y > collision_box.y + collision_box.h) testY = collision_box.y + collision_box.h; // bottom edge

	// get distance from closest edges
	float distX = pos_x - testX;
	float distY = pos_y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	if (distance <= radius) {
		if (distX != 0) return 1;
		if (distY != 0) return 2;
	}
	return false;
}