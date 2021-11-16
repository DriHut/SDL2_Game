#include "GameManager.h"

#include <SDL_image.h>
#include <iostream>
#include "DrawUtil.h"

GameManager::GameManager(const char* title, int width, int height, SDL_Color background_color) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Video and events Initialised!..." << std::endl;
		is_running = true;

		window = new Window(
			title,                  // title
			SDL_WINDOWPOS_CENTERED, // x
			SDL_WINDOWPOS_CENTERED, // y
			width,                  // width
			height,                 // height
			SDL_WINDOW_SHOWN,       // tags
			background_color        // color
		);
		keyboard = new Keyboard();
	}
}

GameManager::~GameManager() {
	clear();
	delete window, keyboard, pusher, ball, title, pause, end;
}

void GameManager::init(int pusher_size, int ball_radius, SDL_Color main_color) {
	// set pusher
	pusher = new Pusher(
		(window->getSize().x - 50) * 0.5, // x pos
		window->getSize().y - 50,         // y pos
		pusher_size,                      // width
		5,                                // height
		main_color,                       // color
		1.0                               // speed
	);

	// create ball with properties
	ball = new Ball(
		pusher->getX() + 0.5 * pusher->getWidth(),      // x pos (centered on the pusher)
		pusher->getY() - 0.5 * pusher->getHeight() - 5, // y pos (on top of the pusher)
		ball_radius,               // radius
		0,                         // vector x
		0.5,                       // speed
		main_color                 // color white
	);

	// general block size parameters
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

	font = TTF_OpenFont("assets/fonts/playmegames-reguler.ttf", 16);
	if (!font) {
		std::cerr << "/!\\Couldn't init font!..." << std::endl;
	}
	else {
		std::cout << "Font loaded correctly!..." << std::endl;
	}

	title_label = new Label("test", font, { 255,255,255,255 }, window->getRenderer());
}

void GameManager::clear() {
	for (Block* block : blocks) {
		delete block;
	}
	blocks.clear();
}

void GameManager::loadLevel(int level) {
	// reset ball position at every new level
	ball->setPos(
		pusher->getX() + 0.5 * pusher->getWidth(),
		pusher->getY() - 0.5 * pusher->getHeight() - ball->getRadius()
	);
	ball->setSpeed(0.5);
	ball->setThrown(false);

	//clear all the blocks
	clear();

	switch (level) {
	case 1: // level 1

		// make a group of block with an increasing level
		for (int j = 0; j < 7; j++) {
			for (int i = -6; i < 6; i++) {
				blocks.push_back(new Block((window->getSize().x - block_Size.x) * 0.5 + i * (block_Size.x + 1), (window->getSize().y - block_Size.y) * 0.5 - j * (block_Size.y + 1), block_Size.x, block_Size.y, 6 - j));
			}
		}
		break;
	}
	
	// set blocks
	/*block = new Block(
		(window->getPos().x - block_Size.x) * 0.5, // x pos
		(window->getPos().y - block_Size.y) * 0.5, // y pos
		block_Size.x,                              // width
		block_Size.y,                              // height
		5                                // hardness / level
	);
	blocks.push_back(block);*/
}

void GameManager::collide(Ball* ball) {
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i]->collision(ball) && blocks[i]->getLevel() < 0) {
			blocks.erase(blocks.begin() + i);
			return; // only one colision considered
		}
	}
	pusher->collision(ball);
}

void GameManager::handleEvents() {
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
				loadLevel(level);
				state++; // exit the waiting menu state
				break;
			case 3:
				std::cout << "Game restarted ! ..." << std::endl;
				loadLevel(level);
				state = 1; // restart to the waiting menu
				break;
			}
		}
		break;
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		// prevent crashing when "unknown key"
		if (event.key.keysym.sym > 0 && event.key.keysym.sym < 322)
			keyboard->updateKey(event.key.keysym.sym, event.key.state);
		break;
	case SDL_MOUSEWHEEL:
		if (!paused) {
			pusher->setSpeed(pusher->getSpeed() + event.wheel.y * 0.1);
		}
		break;
	}
}

void GameManager::update() {

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
		}
		else {
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
			}
			else {
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

void GameManager::render() {
	SDL_Color background_color = window->getBackgroundColor();
	SDL_Renderer* renderer = window->getRenderer();
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a); // reset background everytime
	SDL_RenderClear(renderer);

	// draw pusher at any time
	pusher->render(renderer);

	title_label->render(renderer);

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

void GameManager::clean() {
	clear();
	SDL_Quit();

	std::cout << "Game renderer cleaned!..." << std::endl;
}