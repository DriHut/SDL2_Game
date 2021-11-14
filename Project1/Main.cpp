#include "Game.h"
//#include "Manager.h"

//Manager* game = nullptr;

// frame variables
const int fps = 70;
const int frame_delay = 1000 / fps;
Uint32 frame_last;

// tick variable
const int tps = 70; // might end up being faster (then we will use custom render frame rate)
const int tick_delay = 1000 / tps;
Uint32 tick_start;
int tick_time;

/*int main(int arg, char* args[]) {
	game = new Manager();

	game->initWindow("Carcassone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, false);

	while (game->running()) {

		tick_start = SDL_GetTicks();

		game->handleEvent();
		game->update();

		if (SDL_GetTicks() - frame_last > frame_delay) { // will not render faster than the actual tps
			game->render();
			frame_last = SDL_GetTicks();
		}

		// tick rate (frame rate will be based on if low enough
		tick_time = SDL_GetTicks() - tick_start;
		if (tick_delay > tick_time) {
			SDL_Delay(tick_delay - tick_time);
		}

	}

	game->clean();

	return 0;
}*/

Game* game = nullptr;

int main(int arg, char* args[]) {

	game = new Game();

	game->init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}