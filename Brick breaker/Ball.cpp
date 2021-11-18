#include "Ball.h"
#include <cmath>
#include <iostream>
#include "DrawUtil.h"

#define PI 3.14159265

Ball::Ball(float x, float y, int radius, float vector_x, float speed, SDL_Color color) {
	pos_x = x;
	pos_y = y;

	this->speed = speed;
	vec_x = vector_x;
	vec_y = -sqrt(speed*speed - vector_x*vector_x); // always goes up

	this->color = color;
	this->radius = radius;
}

Ball::~Ball() {}

void Ball::move() {
	pos_x += vec_x;
	pos_y += vec_y;
}

void Ball::setPos(float x, float y) {
	pos_x = x;
	pos_y = y;
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

void Ball::setVectors(float vector_x) {
	vec_x = vector_x;
	vec_y = - sqrt(speed * speed - vector_x * vector_x);  // always goes up
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
		case 2:
			vec_x *= -1;
			vec_y *= -1;
	}
}

float Ball::getSpeed() {
	return speed;
}

void Ball::setSpeed(float speed) {
	float ratio = speed / this->speed;
	vec_x *= ratio;
	vec_y *= ratio;
	this->speed = speed;
}

void Ball::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	DrawUtil::SDL_RenderFillCircle(renderer, (int)pos_x, (int)pos_y, radius);
}

void Ball::setThrown(bool is_thrown) {
	this->is_thrown = is_thrown;
}
