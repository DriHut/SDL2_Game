#include "Button.h"

Button::Button(int x, int y, int w, int h) {
	box->x = x;
	box->y = y;
	box->w = w;
	box->h = h;
}

Button::~Button() {};

bool Button::isHovered(SDL_Point cursor) {
	if (!is_active) return false;
	if (cursor.x > box->x && cursor.x < box->x + box->w && cursor.y > box->y && cursor.y < box->y + box->h) {
		is_hovered = true;
	} else {
		is_hovered = false;
	}
	return is_hovered;
}

void Button::setActive(bool is_active) {
	this->is_active = is_active;
}

void Button::registerCallback(std::function<void()> func) {
	callbacks.push_back(func);
}

void Button::execute() {
	for (std::function<void()> f : callbacks) {
		f();
	}
}