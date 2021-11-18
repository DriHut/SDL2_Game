#pragma once

#include <SDL.h>

class Button {
protected:
	SDL_Rect box;
	bool is_hovered;
	bool is_active = true;
public:
	Button(int x = 0, int y = 0, int w = 0, int h = 0);
	~Button();

	bool isHovered(SDL_Point cursor);
	bool isHovered() { return is_hovered; };

	void setActive(bool is_active);
	bool isActive() { return is_active; };
};