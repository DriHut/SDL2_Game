#include "GameManager.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
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
	delete window, keyboard, pusher, ball, font64, pause_label;
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
		0.7,                       // speed
		main_color                 // color white
	);

	// create cool looking ball menu
	int max_x = window->getSize().x;
	int max_y = window->getSize().y;

	float speed;
	int radius;
	for (int i = 0; i < 15; i++) {
		speed = random(0.5, 2);
		radius = (int)random(3, 15);
		menu_balls.push_back(new Ball((int)random(radius+1,max_x-radius-1), (int)random(radius+1, max_y-radius-1), radius, random(speed), speed, main_color));
	}
	
	// create Blocks for the menu
	int length;
	for (int i = 0; i < 10; i++) {
		length = (int)random(20, 50);
		menu_blocks.push_back(new Block((int)random(length + 1, max_x - length - 1), (int)random(length / 2 + 1, max_y - length / 2 - 1), length, length / 2, (int)random(5)));
	}

	// general block size parameters
	block_Size.x = 50;
	block_Size.y = 25;

	font64 = TTF_OpenFont("assets/fonts/playmegames-reguler.ttf", 64);
	font32 = TTF_OpenFont("assets/fonts/playmegames-reguler.ttf", 32);
	if (!font64 && !font32) {
		std::cerr << "/!\\Couldn't init main font!..." << std::endl;
	}
	else {
		std::cout << "Main font loaded correctly!..." << std::endl;
	}

	// pause label
	pause_label = new Label("Pause", 60, 10, font64, { 255,255,255,255 }, window->getRenderer());
	pause_info = new Label("Press <p> to unpause", window->getSize().x - 300, window->getSize().y - 40, font32, { 255,255,255,255 }, window->getRenderer());

	lost_label = new Label("You Lost", 500, window->getSize().y / 2 + 100, font64, { 255,255,255,255 }, window->getRenderer());
	win_label  = new Label("You Win",  500, window->getSize().y / 2 + 100, font64, { 255,255,255,255 }, window->getRenderer());

	// create a title using a font that will get unloaded
	TTF_Font* temp_font = TTF_OpenFont("assets/fonts/playmegames-reguler.ttf", 256);
	title_label.push_back( new Label("Brick", 150, 100, temp_font, { 255,255,255,255 }, window->getRenderer()) );
	title_label.push_back( new Label("Breaker", 250, 300, temp_font, { 255,255,255,255 }, window->getRenderer()) );
	title_label.push_back( new Label("B", 150, 100, temp_font, { 204,204,0,255 }, window->getRenderer()) );
	title_label.push_back( new Label("B", 250, 300, temp_font, { 204,0,0,255 }, window->getRenderer()) );
	TTF_CloseFont(temp_font);
}

void GameManager::clear() {
	clearBlocks();
	for (Label* label : title_label) {
		delete label;
	}
	title_label.clear();
}

void GameManager::clearBlocks() {
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
	ball->setSpeed(0.7);
	ball->setThrown(false);

	//clear all the blocks
	clearBlocks();

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
	case 1:// in the menu

		// funny graphics in the background
		for (Ball* b : menu_balls) {
			b->move(); // move ball
			if (!window->collide(b)) {
				collide(b);
				for (int i = 0; i < menu_blocks.size(); i++) {
					if (menu_blocks[i]->collision(b) && menu_blocks[i]->getLevel() < 0) {
						delete menu_blocks[i];
						menu_blocks.erase(menu_blocks.begin() + i);

						// recreate a block to replace the old one
						int max_x = window->getSize().x;
						int max_y = window->getSize().y;
						int speed = random(0.5, 2);
						int length = (int)random(20, 50);
						menu_blocks.push_back(new Block((int)random(length + 1, max_x - length - 1), (int)random(length / 2 + 1, max_y - length / 2 - 1), length, length / 2, (int)random(5)));
						break; // only one colision considered
					}
				}
			}
		}
		break;
	case 2: // running state
		if (blocks.size() == 0) {
			state = 4; // really quick way to detect victory state
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
				state++; // loose state
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
	if ((keyboard->getKey(SDLK_q) || keyboard->getKey(SDLK_a)) && pusher->getX() - pusher->getSpeed() > 0) {
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

	// render all the objects
	switch (state) {
	case 1:
		// randomly placed blocks
		for (Block* b : menu_blocks) {
			b->render(renderer);
		}
		// nice looking bouncing balls
		for (Ball* b : menu_balls) {
			b->render(renderer);
		}
		// render all the title labels (for nice looking)
		for (Label* label : title_label) {
			label->render(renderer);
		}
		break;
	case 4:
	case 3: // win or lose cases
		if (state == 4) {
			win_label->render(renderer);
		} else {
			lost_label->render(renderer);
		}
	case 2:
		// render all the blocks
		for (int i = 0; i < blocks.size(); i++) {
			blocks[i]->render(renderer);
		}

		if (!ball->isThrown()) {
			SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255); // reset background everytime
			
			SDL_RenderDrawLine(renderer, ball->getX(), ball->getY(), cursor.x, cursor.y);
		}
		ball->render(renderer);

		if (paused) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			SDL_Rect rect{ 12, 11, 15, 41 };
			SDL_Rect rect_2{ 37, 11, 15, 41 };
			SDL_RenderFillRect(renderer, &rect);
			SDL_RenderFillRect(renderer, &rect_2);

			pause_label->render(renderer);
			pause_info->render(renderer);
		}
		break;
		//SDL_RenderCopy(renderer, end, NULL, NULL);
		break;
	}

	SDL_RenderPresent(renderer);
}

void GameManager::clean() {
	clear();
	SDL_Quit();

	std::cout << "Game renderer cleaned!..." << std::endl;
}

float GameManager::random(float max) {
	return random(0,max);
}

float GameManager::random(float min, float max) {
	float r = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return r;
}