#include "Label.h"

Label::Label(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
	setTexture(text, font, color, renderer);
}

Label::~Label() {}

void Label::setTexture(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
	SDL_DestroyTexture(texture);
	SDL_Surface* tmp = TTF_RenderText_Blended(font, text, color);
	texture = SDL_CreateTextureFromSurface(renderer, tmp);

	// set source box
	source.x = 0;
	source.y = 0;
	source.w = tmp->w;
	source.h = tmp->h;
	
	// set destination box coordinate
	destination.x = 10;
	destination.y = 10;
	destination.w = source.w;
	destination.h = source.h;

	SDL_FreeSurface(tmp);
}

void Label::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &source, &destination);
}