#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Manager {

public:
	Manager();
	~Manager();

	void initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvent();

	void update();

	void renderCentered(int x, int y, SDL_Texture* texture, float scale);
	void render(int x, int y, SDL_Texture* texture, float scale);
	void render();

	void clean();

	bool running() { return is_running; };

	void titleScreen();

private:
	int state = 1;
	SDL_Rect window_dim;
	bool is_running;

};