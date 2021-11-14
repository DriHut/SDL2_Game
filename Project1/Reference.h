#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>

namespace {
	//bool is_running;
	//TTF_Font* Font48 = TTF_OpenFont("assets/font/Toon_Around.ttf", 48);

	SDL_Color WHITE = { 255, 255, 255 };
	SDL_Color BLACK = { 0, 0, 0 };

	SDL_Window* window;
	SDL_Renderer* renderer;
}