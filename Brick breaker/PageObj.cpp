#include "PageObj.h"

bool PageObj::isApplicable(int state) {
	return state == applicable_state;
}

void PageObj::handleEvent(SDL_Event event) {}

void PageObj::update(SDL_Point cursor) {
	// label buttons update
	for (LabelButton* lb : label_buttons) {
		lb->isHovered(cursor);
	}

	// balls and hence blocks update
	for (Ball* b : balls) {
		if (b->isThrown()) {
			b->move(); // move ball

			// check for collisions
			if (!window->collide(b)) {
				//b->collide(blocks,pusher);
			}
		}
	}

	// pusher movement
	if ((keyboard->getKey(SDLK_q) || keyboard->getKey(SDLK_a)) && pusher->getX() - pusher->getSpeed() > 0) {
		pusher->setX(pusher->getX() - pusher->getSpeed());
	} else if (keyboard->getKey(SDLK_d) && pusher->getX() + pusher->getSpeed() + pusher->getWidth() < window->getSize().x) {
		pusher->setX(pusher->getX() + pusher->getSpeed());
	}
}

void PageObj::render(SDL_Renderer* renderer) {
	// labels render
	for (Label* l : labels) {
		if (l->isVisible()) {
			l->render(renderer);
		}
	}

	// label buttons render
	for (LabelButton* lb : label_buttons) {
		if (lb->isVisible()) {
			lb->render(renderer);
		}
	}

	// balls render
	for (Ball* b : balls) {
		if (b->isVisible()) {
			b->render(renderer);
		}
	}

	// blocks render
	for (Block* b : blocks) {
		if (b->isVisible()) {
			b->render(renderer);
		}
	}

	if (pusher->isVisible()) {
		pusher->render(renderer);
	}
}