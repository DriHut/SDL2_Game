#pragma once

#include <SDL.h>
#include <functional>
#include <vector>
#include "UIComponent.h"

class Button: public UIComponent {
protected:
	SDL_Rect* box = new SDL_Rect();
	bool is_hovered = false;
	bool is_active = true;
	std::vector<std::function<void()>> callbacks;
public:
	Button(int x = 0, int y = 0, int w = 0, int h = 0);
	~Button();

	bool isHovered(SDL_Point cursor);
	bool isHovered() { return is_hovered; };

	void setActive(bool is_active);
	bool isActive() { return is_active; };

	void registerCallback(std::function<void()> func);
	void execute();
};