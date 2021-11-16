#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "Window.h"
#include "Block.h"
#include "Pusher.h"
#include "Ball.h"
#include "Keyboard.h"
#include "Label.h"

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

	// Labels
	TTF_Font* font64 = nullptr;
	TTF_Font* font32 = nullptr;
	vector<Label*> title_label;
	Label* pause_label = nullptr;
	Label* pause_info = nullptr;
	Label* lost_label = nullptr;
	Label* win_label = nullptr;

	vector<Ball*> menu_balls; // menu balls
public :
	GameManager(const char* title, int width, int height, SDL_Color background_color);
	~GameManager();

	void init(int pusher_size, int ball_radius, SDL_Color main_color);
	void clear();
	void clearBlocks();

	void loadLevel(int level);

	void collide(Ball* ball);

	void handleEvents();
	void update();
	void render();

	void clean();

	bool isRunning() { return is_running; };

	float random(float max);
	float random(float min, float max);
};