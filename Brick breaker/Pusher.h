#pragma once

#include "Collidable.h"

class Pusher : public Collidable, public Renderable {
private :
	SDL_Color color;
	float speed;
	float x_pos;
public :
	Pusher(int x, int y, int w, int h, SDL_Color color, float speed);
	~Pusher();

	void render(SDL_Renderer* renderer);

	void setX(float x);
	float getX();
	int getY();
	int getWidth();
	int getHeight();

	void setSpeed(float speed);
	float getSpeed();
};