#include "Pusher.h"

Pusher::Pusher(int x, int y, int w, int h, SDL_Color color, float speed) {
	collision_box.x = x;
	collision_box.y = y;
	collision_box.w = w;
	collision_box.h = h;
	this->color = color;
	this->speed = speed;
	x_pos = x;
}

Pusher::~Pusher() {};

void Pusher::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &collision_box);
}

void Pusher::setX(float x) {
	collision_box.x = x;
	x_pos = x;
}

float Pusher::getX() {
	return x_pos;
}

int Pusher::getY() {
	return collision_box.y;
}

int Pusher::getWidth() {
	return collision_box.w;
}

int Pusher::getHeight() {
	return collision_box.h;
}

void Pusher::setSpeed(float speed) {
	if (speed < 5 && speed > 0)
	this->speed = speed;
}

float Pusher::getSpeed() {
	return speed;
}