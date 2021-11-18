#pragma once

#include "Button.h"
#include "Label.h"

class LabelButton : public Button, public Label {
private:
	SDL_Texture* texture_hover;
public:
	LabelButton(const char* text, int x, int y, TTF_Font* font, SDL_Color color, SDL_Color hover_color, SDL_Renderer* renderer);
	~LabelButton() {};

	void setHoverTexture(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
};