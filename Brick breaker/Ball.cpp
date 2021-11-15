#include "Ball.h"
#include <cmath>
#include <iostream>
#include "DrawUtil.h"

Ball::Ball(float x, float y, int radius, float vector_x, int speed, SDL_Color ball_color) {
	ball_pos.x = x;
	ball_pos.y = y;

	this->speed = speed;
	movement_vectors.x = vector_x;
	movement_vectors.y = sqrt(speed*speed - vector_x*vector_x);

	this->ball_color = ball_color;
	this->radius = radius;
}

Ball::~Ball() {}

void Ball::move() {
	ball_pos.x += movement_vectors.x;
	ball_pos.y += movement_vectors.y;
}

int Ball::getX() {
	return ball_pos.x;
}

int Ball::getY() {
	return ball_pos.y;
}

int Ball::getRadius() {
	return radius;
}

int Ball::getVectorX() {
	return movement_vectors.x;
}

int Ball::getVectorY() {
	return movement_vectors.y;
}

SDL_Color Ball::getColor() {
	return ball_color;
}

void Ball::bounce(int angle) {
	movement_vectors.x = -cos(angle) * movement_vectors.x;
	movement_vectors.y = -sin(angle) * movement_vectors.y;
}

void Ball::setSpeed(int speed) {
	float ratio = this->speed / speed;
	movement_vectors.x *= ratio;
	movement_vectors.y *= ratio;
	this->speed = speed;
}

void Ball::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, ball_color.r, ball_color.g, ball_color.b, ball_color.a);
	DrawUtil::SDL_RenderFillCircle(renderer, ball_pos.x, ball_pos.y, radius);
}