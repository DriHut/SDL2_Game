#include "Keyboard.h"

Keyboard::Keyboard() {
	// init keys states to be false
	for (int i = 0; i < 322; i++) {
		KEYS[i] = false;
	}
};

Keyboard::~Keyboard() {};

void Keyboard::updateKey(int key, bool state) {
	KEYS[key] = state;
}

bool Keyboard::getKey(int key) {
	return KEYS[key];
}