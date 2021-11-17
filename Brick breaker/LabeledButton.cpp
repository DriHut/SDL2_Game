#include "LabeledButton.h"

LabeledButton::LabeledButton(const char* text, int x, int y, TTF_Font* font, SDL_Color color, SDL_Color hover_color, SDL_Renderer* renderer) {
	destination.x = x;
	destination.y = y;
	setTexture(text, font, color, renderer);
	setHoverTexture(text, font, hover_color, renderer);
}

void LabeledButton::setHoverTexture(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
	SDL_DestroyTexture(texture);
	SDL_Surface* tmp = TTF_RenderText_Blended(font, text, color);
	texture_hover = SDL_CreateTextureFromSurface(renderer, tmp);

	// set source box
	box.x = destination.x;
	box.y = destination.y;
	box.w = tmp->w;
	box.h = tmp->h;

	SDL_FreeSurface(tmp);
}

void LabeledButton::render(SDL_Renderer* renderer) {
	if (is_hovered) {
		SDL_RenderCopy(renderer, texture_hover, &source, &destination);
	} else {
		SDL_RenderCopy(renderer, texture, &source, &destination);
	}
}