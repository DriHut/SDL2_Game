#pragma once

#include "LabelButton.h"
#include "PageObj.h"

using std::vector;

class Menu : public PageObj {
private :
	// Labels
	vector<Label*> title;

	// Buttons
	LabelButton* play_button = nullptr;
	LabelButton* quit_button = nullptr;

};