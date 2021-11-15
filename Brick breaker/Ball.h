#pragma once

#include <SDL.h>

class Ball {
private: 
	float pos_x; // store x coordinate
	float pos_y; // store y coordinate
	int radius; // ball radius
	int speed; // ball speed
	float vec_x; // stores x between -10 and 10;
	float vec_y; // stores y between -10 and 10;
	SDL_Color color; // ball color
public:
	Ball(float x, float y, int radius, float vector_x, int speed, SDL_Color ball_color);
	~Ball();

	void move();

	int getX();
	int getY();
	int getRadius();

	int getVectorX();
	int getVectorY();

	SDL_Color getColor();

	void bounce(int angle);

	int getSpeed();
	void setSpeed(int speed);

	void render(SDL_Renderer* renderer);
};