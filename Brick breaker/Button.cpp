#include "Button.h"

Button::Button(int x, int y, int w, int h) {
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
}

Button::~Button() {};

bool Button::isHovered(SDL_Point cursor) {
	if (cursor.y > box.y && cursor.x < box.x + box.w && cursor.y > box.y && cursor.y < box.y + box.h) {
		is_hovered = true;
	} else {
		is_hovered = false;
	}
	return is_hovered;
}