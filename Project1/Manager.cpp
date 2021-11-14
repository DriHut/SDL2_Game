#include "Manager.h"
#include <iostream>
#include <SDL_ttf.h>
#include "TextureManager.h"
#include "Reference.h"

SDL_Texture* titles = nullptr;

Manager::Manager() {}
Manager::~Manager() {}

void Manager::initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;
	window_dim.w = width;
	window_dim.x = width / 2;
	window_dim.h = height;
	window_dim.y = height / 2;

	// set flag value for fullscreen
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// Initialise window and renderer
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
		std::cout << "Video and events Initialised!..." << std::endl;

		// create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "window created!..." << std::endl;
		}
		else {
			std::cerr << "/!\\Couldn't init window!..." << std::endl;
		}

		// create renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created!..." << std::endl;
		}
		else {
			std::cerr << "/!\\Couldn't create render!..." << std::endl;
		}

		//set the window icon
		SDL_SetWindowIcon(window, TextureManager::loadSurface("assets/CCSN_Icon.png"));
		titles = TextureManager::loadTexture("assets/CCSN_Title.png");
		is_running = true;
	}
	else {
		std::cerr << "/!\\Couldn't init!..." << std::endl;
		is_running = false;
	}
}

void Manager::handleEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT: // when window closed
		is_running = false;
		break;
	default:
		break;
	}
}

void Manager::update() {

}

void Manager::renderCentered(int x, int y, SDL_Texture* texture, float scale = 1) {

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	// set height and width from the source texture
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	// set point to the center
	dst.x = 640 / 2 - src.w / 2 + x;
	dst.y = 480 / 2 - src.h / 2 + y;
	// scale the texture
	dst.w = src.w * scale;
	dst.h = src.h * scale;

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Manager::render(int x, int y, SDL_Texture* texture, float scale = 0) {

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	// set height and width from the source texture
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	// set point to the center
	dst.x = x;
	dst.y = y;
	// scale the texture
	dst.w = src.w * scale;
	dst.h = src.h * scale;

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Manager::render() { // rendering
	SDL_RenderClear(renderer); // start renderer

	// game render part
	switch (state) {
	case 0:
		titleScreen();
		break;
	}

	SDL_RenderPresent(renderer); // push render
}

void Manager::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game renderer cleaned!..." << std::endl;
}

void Manager::titleScreen() {
	renderCentered(window_dim.x, window_dim.h / 10, titles, 0.5);
}