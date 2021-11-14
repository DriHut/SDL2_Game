#include "Game.h"
#include "Reference.h"

SDL_Texture* texture;

Game::Game() {};
Game::~Game() {};

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	// set flag value for fullscreen
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// Initialise window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		
		is_running = true;
	} else {
		is_running = false;
	}

	SDL_Surface* tmpSurface = IMG_Load("assets/tile_1.png");
	texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
};

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT: // when window closed
		is_running = false;
		break;
	default:
		break;
	}
};

void Game::update() {};

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
};

void Game::clean() {};