#pragma once

#include "Button.h"
#include "Renderable.h"

class IconButton : public Button, public Renderable {
private:
	SDL_Rect source;

	SDL_Texture* texture = nullptr;
	SDL_Rect destination;

	SDL_Texture* texture_hover = nullptr;
	SDL_Rect hover_destination;
public:
	IconButton(SDL_Surface* texture, int x, int y, SDL_Color color, SDL_Color hover_color, SDL_Renderer* renderer, float scale = 1);
	~IconButton();

	void setTexture(SDL_Surface* texture, SDL_Color color, SDL_Renderer* renderer, float scale = 1);
	void setHoverTexture(SDL_Surface* texture, SDL_Color color, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
};