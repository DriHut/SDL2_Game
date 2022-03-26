#include "IconButton.h"

IconButton::IconButton(SDL_Surface* texture, int x, int y, SDL_Color color, SDL_Color hover_color, SDL_Renderer* renderer, float scale) {
	destination.x = x;
	destination.y = y;
	setTexture(texture, color, renderer, scale);
	setHoverTexture(texture, hover_color, renderer);

	// set bounding box
	box = &destination;
}

IconButton::~IconButton() {
	delete texture, texture_hover;
}

void IconButton::setTexture(SDL_Surface* init_texture, SDL_Color color, SDL_Renderer* renderer, float scale) {
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, init_texture);
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

	// set source box
	source.x = 0;
	source.y = 0;
	source.w = init_texture->w;
	source.h = init_texture->h;

	// set destination box coordinate
	destination.w = source.w * scale;
	destination.h = source.h * scale;
}

void IconButton::setHoverTexture(SDL_Surface* init_texture, SDL_Color color, SDL_Renderer* renderer) {
	SDL_DestroyTexture(texture_hover);
	texture_hover = SDL_CreateTextureFromSurface(renderer, init_texture);
	SDL_SetTextureColorMod(texture_hover, color.r, color.g, color.b);

	hover_destination = destination;
	hover_destination.y -= destination.h * 0.02;
	hover_destination.x -= destination.h * 0.02;
}

void IconButton::render(SDL_Renderer* renderer) {
	if (!is_active) return;
	SDL_RenderCopy(renderer, texture, &source, &destination);
	if (is_hovered) SDL_RenderCopy(renderer, texture_hover, &source, &hover_destination);
}
