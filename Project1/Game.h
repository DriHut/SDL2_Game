#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return is_running; };

private:
	bool is_running;
};