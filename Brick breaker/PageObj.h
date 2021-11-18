#pragma once

#include <vector>
#include "Window.h"
#include "Keyboard.h"
#include "Block.h"
#include "Pusher.h"
#include "Ball.h"
#include "LabelButton.h"

using std::vector;

class PageObj {
protected :
	// util
	int applicable_state;
	Window* window = nullptr;
	Keyboard* keyboard = nullptr;

	// components
	vector<Label*> labels; // labels
	vector<LabelButton*> label_buttons; // label buttons

	// Objects
	vector<Ball*> balls; // balls
	vector<Block*> blocks; // blocks
	Pusher* pusher = nullptr; // pusher
public :
	PageObj(int applicable_state, Window* window, Keyboard* keyboard) : applicable_state{ applicable_state }, window{ window }, keyboard { keyboard }{};
	~PageObj() {};

	bool isApplicable(int state);

	void handleEvent(SDL_Event event);
	void update(SDL_Point cursor);
	void render(SDL_Renderer* renderer);

	void clean();
};