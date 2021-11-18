#include "Label.h"

Label::Label(const char* text, int x, int y, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
	destination.x = x;
	destination.y = y;
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
	destination.w = source.w;
	destination.h = source.h;

	SDL_FreeSurface(tmp);
}

void Label::render(SDL_Renderer* renderer) {
	if (is_visible) {
		SDL_RenderCopy(renderer, texture, &source, &destination);
	}
}

void Label::setVisible(bool is_visible) {
	this->is_visible = is_visible;
}