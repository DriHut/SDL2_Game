#include "Label.h"

Label::Label(const char* text, int x, int y, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, float scale) {
	destination.x = x;
	destination.y = y;
	setTexture(text, font, color, renderer, scale);
}

Label::~Label() {
	// delete texture;
}

void Label::setTexture(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, float scale) {
	SDL_DestroyTexture(texture);
	SDL_Surface* tmp = TTF_RenderText_Blended(font, text, color);
	texture = SDL_CreateTextureFromSurface(renderer, tmp);

	// set source box
	source.x = 0;
	source.y = 0;
	source.w = tmp->w;
	source.h = tmp->h;
	
	// set destination box coordinate
	destination.w = source.w * scale;
	destination.h = source.h * scale;

	SDL_FreeSurface(tmp);
}

void Label::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &source, &destination);
}