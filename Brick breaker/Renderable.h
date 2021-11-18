#pragma once

class Renderable {
protected:
	bool is_visible = true;
public:
	Renderable() {};
	~Renderable() {};

	void setVisible(bool is_visible) { this->is_visible = is_visible; };
	bool isVisible() { return is_visible; };
};