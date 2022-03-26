#include "LabelButton.h"

LabelButton::LabelButton(const char* text, int x, int y, TTF_Font* font, SDL_Color color, SDL_Color hover_color, SDL_Renderer* renderer, float scale) : Label(text, x, y, font, color, renderer) {
	setHoverTexture(text, font, hover_color, renderer);

	// set bounding box
	box = &destination;
}

LabelButton::~LabelButton() {
	delete texture_hover;
}

void LabelButton::setHoverTexture(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
	SDL_DestroyTexture(texture_hover);
	SDL_Surface* tmp = TTF_RenderText_Blended(font, text, color);
	texture_hover = SDL_CreateTextureFromSurface(renderer, tmp);

	hover_destination = destination;
	hover_destination.y -= destination.h * 0.02;
	hover_destination.x -= destination.h * 0.02;

	SDL_FreeSurface(tmp);
}

void LabelButton::render(SDL_Renderer* renderer) {
	if (!is_active) return;
	Label::render(renderer);
	if (is_hovered) SDL_RenderCopy(renderer, texture_hover, &source, &hover_destination);
}