#include <SDL.h>
#include <iostream>

bool is_running;
int state = 1; // state define which is the current process

// window properties
SDL_Color background_color = { 255, 255, 255, 255 }; // background color (white)
SDL_Point window_pos; // heigh and width (using point because rectangle stores 2 extra values == 2 useless value)
SDL_Window* window = nullptr; // stores window instance
SDL_Renderer* renderer = nullptr; // store renderer instance

// ball properties
SDL_Rect ball_pos; // store x y coordinate and height and width
SDL_Point movement_vectors; // stores x and y between -10 and 10;
SDL_Color ball_color; // ball color

// rneder / process properties

// frame variables
const int fps = 70; // max since it can't be faster than tps
const int frame_delay = 1000 / fps;
Uint32 frame_last;

// tick variable
float tps = 30; // might end up being faster (then we will use custom render frame rate)
int tick_delay = 1000 / tps;
Uint32 tick_last;

void move() {
	ball_pos.x += movement_vectors.x;
	ball_pos.y += movement_vectors.y;
}

void collision() {
	int next_x = ball_pos.x + movement_vectors.x;
	if (next_x < 0 || next_x + ball_pos.w > window_pos.x) {
		movement_vectors.x = -movement_vectors.x;
	}
	int next_y = ball_pos.y + movement_vectors.y;
	if (next_y < 0 || next_y + ball_pos.h > window_pos.y) {
		movement_vectors.y = -movement_vectors.y;
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
		if (event.button.button == SDL_BUTTON_LEFT && state == 1) {
			std::cout << "Game started ! ..." << std::endl;
			state++; // exist the waiting menu state
		}
		break;
	default:
		break;
	}
}

void update() {
	switch (state) {
	case 2:
		move();
		collision();
		break;
	}
}

void render() {
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a); // reset background everytime
	SDL_RenderClear(renderer);

	// render ball
	SDL_SetRenderDrawColor(renderer, ball_color.r, ball_color.g, ball_color.b, ball_color.a);
	SDL_RenderFillRect(renderer, &ball_pos);

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

		window_pos.x = 600; // window width
		window_pos.y = 400; // window height
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

	// create ball properties
	ball_pos.w = 10;
	ball_pos.h = ball_pos.w; // square
	ball_pos.x = (window_pos.x - ball_pos.w) * 0.5; // 1/2 of window width - the width to be centered
	ball_pos.y = window_pos.y * 0.75 - 0.5 * ball_pos.h; // 3/4 of window height - the height to be centered
	movement_vectors.x = 0; // x movement vector
	movement_vectors.y = 2; // y movement vector
	ball_color = { 0, 0, 0, 255 }; // black

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