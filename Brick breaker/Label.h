#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderable.h"
#include "UIComponent.h"

class Label: public Renderable, public UIComponent {
protected :
	SDL_Rect source;
	SDL_Rect destination;
	SDL_Texture* texture = nullptr;
public :
	Label(const char* text, int x, int y, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, float scale = 1);
	~Label();

	void setTexture(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, float scale = 1);
	void render(SDL_Renderer* renderer);
};