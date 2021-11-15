#pragma once

#include <SDL.h>

class Ball {
private: 
	float pos_x; // store x coordinate
	float pos_y; // store y coordinate

	int radius; // ball radius

	float speed; // ball speed

	float vec_x; // stores x between -1 and 1;
	float vec_y; // stores y between -1 and 1;

	SDL_Color color; // ball color
	bool is_thrown = false; // get if ball has been launched 
public:
	Ball(float x, float y, int radius, float vector_x, float speed, SDL_Color ball_color);
	~Ball();

	void move();

	void setPos(float x, float y);

	int getX();
	int getY();
	int getRadius();

	void setVectors(float vector_x);

	int getVectorX();
	int getVectorY();

	SDL_Color getColor();

	void bounce(int angle);

	int getSpeed();
	void setSpeed(float speed);

	void render(SDL_Renderer* renderer);

	bool isThrown() { return is_thrown; };
	void setThrown(bool is_thrown);
};