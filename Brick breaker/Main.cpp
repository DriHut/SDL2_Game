#include "GameManager.h"

// frame variables
const int fps = 70; // max since it can't be faster than tps
const int frame_delay = 1000 / fps;
Uint32 frame_last;

// tick variable
float tps = 500; // might end up being faster (then we will use custom render frame rate)
int tick_delay = 1000 / tps;
Uint32 tick_last;

GameManager* game = nullptr;

int main(int arg, char* args[]) {
	game = new GameManager("Brick Breaker", 1280, 720, { 50, 50, 50, 255 });

	game->init( 50, 5, { 255, 255, 255, 255 });

	while (game->isRunning()) {
		game->handleEvents();

		// tick rate (no delay to handle events corretly)
		if (SDL_GetTicks() - tick_last > tick_delay) {
			game->update();
			tick_last = SDL_GetTicks();
		}

		// fps
		if (SDL_GetTicks() - frame_last > frame_delay) {
			game->render();
			frame_last = SDL_GetTicks();
		}
	}

	game->clean();
	delete game;

	return 0;
}