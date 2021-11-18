#pragma once

#include <vector>
#include "Block.h"
#include "Pusher.h"
#include "Ball.h"

using std::vector;

class PageObj {
protected :
	int applicable_state;

	// Objects
	vector<Ball*> balls; // balls
	vector<Block*> blocks; // blocks
	Pusher* pusher = nullptr; // pusher
public :
	PageObj(int applicable_state) : applicable_state{ applicable_state } {};
	~PageObj() {};
};