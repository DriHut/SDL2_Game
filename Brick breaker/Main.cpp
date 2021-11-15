#include <SDL.h>
#include <iostream>
#include "DrawUtil.h"
#include "Ball.h"

bool is_running;
int state = 1; // state define which is the current process

// window properties
SDL_Color background_color = { 255, 255, 255, 255 }; // background color (white)
SDL_Point window_pos; // heigh and width (using point because rectangle stores 2 extra values == 2 useless value)
SDL_Window* window = nullptr; // stores window instance
SDL_Renderer* renderer = nullptr; // store renderer instance

Ball* ball = nullptr;

// rneder / process properties

// frame variables
const int fps = 70; // max since it can't be faster than tps
const int frame_delay = 1000 / fps;
Uint32 frame_last;

// tick variable
float tps = 120; // might end up being faster (then we will use custom render frame rate)
int tick_delay = 1000 / tps;
Uint32 tick_last;

void collision() {
	int next_x = ball->getX() + ball->getVectorX();
	if (next_x - ball->getRadius() < 0 || next_x + ball->getRadius() > window_pos.x) {
		ball->bounce(0);
	}
	int next_y = ball->getY() + ball->getVectorY();
	if (next_y - ball->getRadius() < 0) {
		ball->bounce(1);
	} else if (next_y + ball->getRadius() > window_pos.y) {
		state++;
		ball->bounce(1);
		std::cout << "Game ended! ..." << std::endl;
	}
}

void handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT: // when window closed
		is_running = false;
		break;
	case SDL_MOUSEBUTTONUP: // check when click finished
		if (event.button.button == SDL_BUTTON_LEFT) {
			switch (state) {
			case 1:
				std::cout << "Game started ! ..." << std::endl;
				state++; // exit the waiting menu state
				break;
			case 3:
				std::cout << "Game restarted ! ..." << std::endl;
				state = 1; // restart to the waiting menu
				break;
			}
		}
		break;
	default:
		break;
	}
}

void update() {
	switch (state) {
	case 2:
		ball->move();
		collision();
		break;
	}
}

void render() {
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a); // reset background everytime
	SDL_RenderClear(renderer);

	// render ball
	ball->render(renderer);

	SDL_RenderPresent(renderer);
}

void clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game renderer cleaned!..." << std::endl;
}

int main(int arg, char* args[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Video and events Initialised!..." << std::endl;

		window_pos.x = 1280; // window width
		window_pos.y = 720; // window height
		window = SDL_CreateWindow("Brick breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_pos.x, window_pos.y, SDL_WINDOW_SHOWN);
		if (window) {
			std::cout << "window created!..." << std::endl;
			is_running = true;
		} else {
			std::cerr << "/!\\Couldn't init window!..." << std::endl;
		}


		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created!..." << std::endl;
		}
		else {
			std::cerr << "/!\\Couldn't create render!..." << std::endl;
		}
	}

	// create ball with properties
	ball = new Ball(
		(window_pos.x - 5) * 0.5,      // x pos (centered on the window)
		window_pos.y * 0.75 - 0.5 * 5, // y pos (centered on the window)
		5,                             // radius
		0.4,                           // vector x
		1,                             // speed
		{ 0,0,0,255 }                  // color black
	);

	while (is_running) {
		handleEvents();

		// tick rate (no delay to handle events corretly)
		if (SDL_GetTicks() - tick_last > tick_delay) {
			update();
			tick_last = SDL_GetTicks();
		}

		// fps
		if (SDL_GetTicks() - frame_last > frame_delay) {
			render();
			frame_last = SDL_GetTicks();
		}
	}

	clean();

	return 0;
}