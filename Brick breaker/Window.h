#pragma once

#include <SDL.h>
#include "Ball.h"

class Window {
private:
	SDL_Color background_color; // background color
	SDL_Point pos; // heigh and width (using point because rectangle stores 2 extra values == 2 useless value)
	SDL_Window* window = nullptr; // stores window instance
	SDL_Renderer* renderer = nullptr; // store renderer instance
public:
	Window(const char* title, int x, int y, int width, int height, Uint32 flags, SDL_Color background_color);
	~Window();

	bool stopCollide(Ball* ball);

	bool collide(Ball* ball);

	SDL_Point getPos() { return pos; };
	SDL_Color getBackgroundColor() { return background_color; };
	SDL_Window* getWindow() { return window; };
	SDL_Renderer* getRenderer() { return renderer; };

};