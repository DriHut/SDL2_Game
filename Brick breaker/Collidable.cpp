#include "Collidable.h"

Collidable::Collidable(int x, int y, int w, int h) {
	collision_box.x = x;
	collision_box.y = y;
	collision_box.w = w;
	collision_box.h = h;
};

Collidable::~Collidable() {};

bool Collidable::collision(Ball* ball) {
	int collision = collide(ball->getX(), ball->getY(), ball->getRadius());
	if (collision != 0) {
		ball->bounce(collision - 1);
		return true;
	}
	return false;
}

int Collidable::collide(int pos_x, int pos_y, int radius) {

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