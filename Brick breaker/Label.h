#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderable.h"

class Label: public Renderable {
protected :
	SDL_Rect source;
	SDL_Rect destination;
	SDL_Texture* texture;
public :
	Label() {};
	Label(const char* text, int x, int y, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
	~Label();

	void setTexture(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
};