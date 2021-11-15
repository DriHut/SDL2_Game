#include <SDL.h>
#include <iostream>
#include <vector>
#include "DrawUtil.h"
#include "Window.h"
#include "Block.h"
#include "Ball.h"

using std::vector;

bool is_running;
int state = 1; // state define which is the current process
Window* window = nullptr;

Ball* ball = nullptr; // main ball
//vector<Ball*> balls; // power balls
int level = 1;

//SDL_Rect collidable;
Block* block = nullptr;

void init() {
	switch (level) {
	case 1:
		ball->setPos(window->getPos().x * 0.5, window->getPos().y * 0.75);
		ball->setSpeed(0.5);
		ball->setVectors(0);
		break;
	}
}

void clear() {
	//balls.clear();
}

void collide(Ball* ball) {
	if (block->collision(ball) && block->getLevel() < 0) {
		delete block;
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
				clear();
				init();
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
		if (window->stopCollide(ball)) {
			state++;
			break;
		}
		if (!window->collide(ball)) {
			collide(ball);
		}
		break;
	}
}

void render() {
	SDL_Color background_color = window->getBackgroundColor();
	SDL_Renderer* renderer = window->getRenderer();
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a); // reset background everytime
	SDL_RenderClear(renderer);

	// render ball
	ball->render(renderer);
	block->render(renderer);

	SDL_RenderPresent(renderer);
}

void clean() {
	SDL_DestroyWindow(window->getWindow());
	SDL_DestroyRenderer(window->getRenderer());
	SDL_Quit();

	std::cout << "Game renderer cleaned!..." << std::endl;
}

// frame variables
const int fps = 70; // max since it can't be faster than tps
const int frame_delay = 1000 / fps;
Uint32 frame_last;

// tick variable
float tps = 500; // might end up being faster (then we will use custom render frame rate)
int tick_delay = 1000 / tps;
Uint32 tick_last;

int main(int arg, char* args[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Video and events Initialised!..." << std::endl;
		is_running = true;

		window = new Window(
			"Brick breaker",        // title
			SDL_WINDOWPOS_CENTERED, // x
			SDL_WINDOWPOS_CENTERED, // y
			1280,                   // width
			720,                    // height
			SDL_WINDOW_SHOWN,       // tags
			{ 255, 255, 255, 255 }  // color
		);
	}

	// set test block
	block = new Block((window->getPos().x - 20) * 0.5, (window->getPos().y - 10) * 0.5, 20, 10, 5);

	// create ball with properties
	ball = new Ball(
		window->getPos().x * 0.5,  // x pos (centered on the window)
		window->getPos().y * 0.75, // y pos (centered on the window)
		5,                         // radius
		0,                         // vector x
		0.5,                       // speed
		{ 0,0,0,255 }              // color black
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