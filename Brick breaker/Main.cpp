#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "DrawUtil.h"
#include "Window.h"
#include "Block.h"
#include "Pusher.h"
#include "Ball.h"
#include "Keyboard.h"

using std::vector;

bool is_running; // is game running 
int level = 1; // current loaded level
int state = 1; // state define which is the current process
Window* window = nullptr; // store multiple variables relative to the window
Keyboard* keyboard = nullptr; // stores all key states

bool released = true; // save for pause button state
bool paused; // paused state

Ball* ball = nullptr; // main ball
//vector<Ball*> balls; // power balls

vector<Block*> blocks; // blocks list
SDL_Point block_Size;

Pusher* pusher = nullptr;
SDL_Point cursor;

// not clean implementation
SDL_Texture* title = nullptr;
SDL_Texture* pause = nullptr;
SDL_Texture* end = nullptr;

void init() {
	ball->setPos(
		pusher->getX() + 0.5 * pusher->getWidth(),
		pusher->getY() - 0.5 * pusher->getHeight() - ball->getRadius()
	);
	ball->setSpeed(0.5);
	ball->setThrown(false);

	block_Size.x = 50;
	block_Size.y = 25;

	// draw start image
	SDL_Surface* tmp = IMG_Load("assets/Start_screen.png");
	title = SDL_CreateTextureFromSurface(window->getRenderer(), tmp);
	// draw pause image
	tmp = IMG_Load("assets/Pause_screen.png");
	pause = SDL_CreateTextureFromSurface(window->getRenderer(), tmp);
	// draw end image
	tmp = IMG_Load("assets/End_screen.png");
	end = SDL_CreateTextureFromSurface(window->getRenderer(), tmp);
	SDL_FreeSurface(tmp); // unload the surface

	switch (level) {
	case 1: // level 1
		// set blocks
		/*block = new Block(
			(window->getPos().x - block_Size.x) * 0.5, // x pos
			(window->getPos().y - block_Size.y) * 0.5, // y pos
			block_Size.x,                              // width
			block_Size.y,                              // height
			5                                // hardness / level 
		);
		blocks.push_back(block);*/

		for (int j = 0; j < 7; j++) {
			for (int i = -6; i < 6; i++) {
				blocks.push_back(new Block((window->getSize().x - block_Size.x) * 0.5 + i * (block_Size.x+1), (window->getSize().y - block_Size.y) * 0.5 - j * (block_Size.y + 1), block_Size.x, block_Size.y, 6 - j));
			}
		}
		break;
	}
}

void clear() {
	//balls.clear();
	for (Block* block : blocks) {
		delete block;
	}
	blocks.clear();
}

void collide(Ball* ball) {
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i]->collision(ball) && blocks[i]->getLevel() < 0) {
			blocks.erase(blocks.begin()+i);
			return; // only one colision considered
		}
	}
	pusher->collision(ball);
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
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		keyboard->updateKey(event.key.keysym.sym, event.key.state);
		break;
	case SDL_MOUSEWHEEL:
		if (!paused) {
			pusher->setSpeed(pusher->getSpeed() + event.wheel.y * 0.1);
			std::cout << "speed: " << pusher->getSpeed() << std::endl;
		}
		break;
	}
}

void update() {

	switch (state) {
	case 2: // running state
		if (blocks.size() == 0) {
			state++; // really quick way to detect end condition
		}

		// handle pause
		if (keyboard->getKey(SDLK_p) && released) {
			paused = !paused;
			released = false;
		}
		else if (!keyboard->getKey(SDLK_p) && !released) {
			released = true;
		}
		if (paused) { return; }

		if (ball->isThrown()) {
			ball->move(); // move ball

			// check for collisions
			if (window->stopCollide(ball)) {
				state++;
				break;
			}
			if (!window->collide(ball)) {
				collide(ball);
			}
		} else {
			ball->setPos(
				pusher->getX() + 0.5 * pusher->getWidth(),
				pusher->getY() - 0.5 * pusher->getHeight() - ball->getRadius()
			);
			// determine throwing direction (unfinished)
			int x, y;
			SDL_GetGlobalMouseState(&cursor.x, &cursor.y);
			SDL_GetWindowPosition(window->getWindow(), &x, &y);

			// normalize cursor position relatively to the window
			cursor.x -= x;
			cursor.y -= y;

			// get vectors
			int  vect_x;
			if (cursor.y < ball->getY()) {
				vect_x = cursor.x - ball->getX();
			} else {
				vect_x = ball->getX() - cursor.x;
			}
			int  vect_y = -abs(ball->getY() - cursor.y);

			float length = sqrt(vect_x * vect_x + vect_y * vect_y);
			float speed = ball->getSpeed();

			if (keyboard->getKey(SDLK_SPACE)) {
				ball->setThrown(true);
				ball->setVectors(vect_x * (speed / length));
			}

			// factor to render a line that is long enough
			cursor.x = ball->getX() + vect_x * (speed * 80 / length);
			cursor.y = ball->getY() + vect_y * (speed * 80 / length);
		}
		break;
	}

	// pusher movement
	if (keyboard->getKey(SDLK_q) && pusher->getX() - pusher->getSpeed() > 0) { // fast moves
		pusher->setX(pusher->getX() - pusher->getSpeed());
	}
	else if (keyboard->getKey(SDLK_d) && pusher->getX() + pusher->getSpeed() + pusher->getWidth() < window->getSize().x) {
		pusher->setX(pusher->getX() + pusher->getSpeed());
	}
}

void render() {
	SDL_Color background_color = window->getBackgroundColor();
	SDL_Renderer* renderer = window->getRenderer();
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a); // reset background everytime
	SDL_RenderClear(renderer);

	// draw pusher at any time
	pusher->render(renderer);

	// render all the objects
	switch (state) {
	case 1:
		SDL_RenderCopy(renderer, title, NULL, NULL);
		break;
	case 2:
		// render all the blocks
		for (int i = 0; i < blocks.size(); i++) {
			blocks[i]->render(renderer);
		}

		if (!ball->isThrown()) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // reset background everytime

			SDL_RenderDrawLine(renderer, ball->getX(), ball->getY(), cursor.x, cursor.y);
		}
		ball->render(renderer);

		if (paused) {
			SDL_RenderCopy(renderer, pause, NULL, NULL);
		}
		break;
	case 3:
		SDL_RenderCopy(renderer, end, NULL, NULL);
		break;
	}

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
			{ 50, 50, 50, 255 }     // color
		);
		keyboard = new Keyboard();
	}

	// set pusher
	pusher = new Pusher(
		(window->getSize().x - 50) * 0.5, // x pos
		window->getSize().y - 50,         // y pos
		50,                              // width
		5,                               // height
		{ 255, 255, 255, 255 },          // color
		1.0                              // speed
	);

	// create ball with properties
	ball = new Ball(
		pusher->getX() + 0.5 * pusher->getWidth(),      // x pos (centered on the pusher)
		pusher->getY() - 0.5 * pusher->getHeight() - 5, // y pos (on top of the pusher)
		5,                         // radius
		0,                         // vector x
		0.5,                       // speed
		{ 255,255,255,255 }        // color white
	);

	init();

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