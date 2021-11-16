#pragma once
#include <SDL.h>
#include <vector>
#include "Window.h"
#include "Block.h"
#include "Pusher.h"
#include "Ball.h"
#include "Keyboard.h"

using std::vector;

class GameManager {
private:
	// state variables
	bool released = true; // save for pause button state
	bool paused; // paused state
	int state = 1; // state define which is the current process
	int level = 1; // save the currently played level
	SDL_Point block_Size; // size of the blocks set in the initialisation procedure

	// window related variables
	Window* window = nullptr; // store multiple variables relative to the window
	Keyboard* keyboard = nullptr; // stores all key states
	bool is_running; // is game running 

	//vector<Ball*> balls; // power balls

	// objects
	Pusher* pusher = nullptr;
	Ball* ball = nullptr; // main ball
	vector<Block*> blocks; // blocks list
	SDL_Point cursor;

	// Textures (not clean implementation)
	SDL_Texture* title = nullptr;
	SDL_Texture* pause = nullptr;
	SDL_Texture* end = nullptr;
public :
	GameManager(const char* title, int pusher_size, int ball_radius, int width, int height, SDL_Color background_color, SDL_Color main_color);
	~GameManager();

	void init();
	void clear();

	void loadLevel(int level);

	void collide(Ball* ball);

	void handleEvents();
	void update();
	void render();

	void clean();

	bool isRunning() { return is_running; };
};