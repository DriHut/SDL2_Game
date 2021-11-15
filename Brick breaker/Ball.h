#pragma once

#include <SDL.h>

class Ball {
private: 
	SDL_Point ball_pos; // store x y coordinate
	int radius; // ball radius
	int speed; // ball speed
	SDL_Point movement_vectors; // stores x and y between -10 and 10;
	SDL_Color ball_color; // ball color
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
	void setSpeed(int speed);

	void render(SDL_Renderer* renderer);
};