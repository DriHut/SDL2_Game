#pragma once

class Keyboard {
private :
	bool KEYS[322];
public :
	Keyboard();
	~Keyboard();

	void updateKey(int key, bool state);
	bool getKey(int key);
};