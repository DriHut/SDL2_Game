#include "Window.h"
#include <iostream>

Window::Window(const char* title, int x, int y, int width, int height, Uint32 flags, SDL_Color background_color) {
	box.x = x; // window x
	box.y = y; // window y
	box.w = width; // window width
	box.h = height; // window height
	window = SDL_CreateWindow(title, x, y, width, height, flags);
	if (window) {
		std::cout << "window created!..." << std::endl;
	}
	else {
		std::cerr << "/!\\Couldn't init window!..." << std::endl;
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer) {
		std::cout << "renderer created!..." << std::endl;
	}
	else {
		std::cerr << "/!\\Couldn't create render!..." << std::endl;
	}

	//load font :!\ doesn't work on my IDE sadly
	/*if (TTF_Init()) {
		std::cout << "ttf library initialised created!..." << std::endl;
	}
	else {
		std::cerr << "/!\\Couldn't init fonts!..." << std::endl;
	}*/
	this->background_color = background_color;
}

Window::~Window() {
	delete window, renderer;
}

bool Window::collide(Ball* ball) { // get when colliding with borders
	bool collided = false;
	int next_x = ball->getX() + ball->getVectorX();
	if (next_x - ball->getRadius() < 0 || next_x + ball->getRadius() > box.w) {
		ball->bounce(0);
		collided =  true;
	}
	int next_y = ball->getY() + ball->getVectorY();
	if (next_y - ball->getRadius() < 0) {
		ball->bounce(1);
		collided =  true;
	}
	return collided;
}

bool Window::stopCollide(Ball* ball) { // get when touching lower border
	int next_y = ball->getY() + ball->getVectorY();
	if (next_y + ball->getRadius() > box.h) {
		ball->bounce(1);
		std::cout << "Game ended! ..." << std::endl;
		return true;
	}
	return false;
}

SDL_Point Window::getSize() {
	SDL_Point size;
	size.x = box.w;
	size.y = box.h;
	return size;
}

SDL_Point Window::getPos() {
	SDL_Point pos;
	pos.x = box.x;
	pos.y = box.y;
	return pos;
}