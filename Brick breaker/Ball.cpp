#include "Ball.h"
#include <cmath>
#include <iostream>
#include "DrawUtil.h"

#define PI 3.14159265

Ball::Ball(float x, float y, int radius, float vector_x, int speed, SDL_Color color) {
	pos_x = x;
	pos_y = y;

	this->speed = speed;
	vec_x = vector_x;
	vec_y = sqrt(speed*speed - vector_x*vector_x);

	this->color = color;
	this->radius = radius;
}

Ball::~Ball() {}

void Ball::move() {
	pos_x += vec_x;
	pos_y += vec_y;
}

int Ball::getX() {
	return pos_x;
}

int Ball::getY() {
	return pos_y;
}

int Ball::getRadius() {
	return radius;
}

int Ball::getVectorX() {
	return vec_x;
}

int Ball::getVectorY() {
	return vec_y;
}

SDL_Color Ball::getColor() {
	return color;
}

void Ball::bounce(int angle) {
	switch (angle) {
	case 0:
		vec_x *= -1;
		break;
	case 1:
		vec_y *= -1;
		break;
	default:
		break;
	}
}

int Ball::getSpeed() {
	return speed;
}

void Ball::setSpeed(int speed) {
	float ratio = (float)(speed) / (float)(this->speed);
	vec_x *= ratio;
	vec_y *= ratio;
	this->speed = speed;
	std::cout << vec_x << " " << vec_y << std::endl;
}

void Ball::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	DrawUtil::SDL_RenderFillCircle(renderer, (int)pos_x, (int)pos_y, radius);
}
