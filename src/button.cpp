#pragma once

#include "utils.cpp"

class Button
{
public:
	void init();
	void place(int, int);
	void resize(int, int);
	SDL_Rect *getRect();
	SDL_Rect *getNormalRect();
	int getColorRed();
	int getColorGreen();
	int getColorBlue();
	bool mouseMotion(int, int);
	bool leftMouseDown(int, int);
	bool leftMouseUp(int, int);
	void update();
private:
	SDL_Rect normalrect;
	SDL_Rect downrect;
	bool hasFocus;
	bool hadFocus;
	bool down;
	AnimatedInt red;
	AnimatedInt green;
	AnimatedInt blue;
};

void Button::init() {
	this->hasFocus = false;
	this->hadFocus = true;
	this->down = false;
}

void Button::place(int x, int y) {
	this->normalrect.x = x;
	this->normalrect.y = y;
	this->downrect.x = x+2;
	this->downrect.y = y+2;
}

void Button::resize(int w, int h) {
	this->normalrect.w = w;
	this->normalrect.h = h;
	this->downrect.w = w-4;
	this->downrect.h = h-4;
}

SDL_Rect *Button::getRect() {
	if (this->down) {
		return &this->downrect;
	} else {
		return &this->normalrect;
	}
}

SDL_Rect *Button::getNormalRect() {
	return &this->normalrect;
}

int Button::getColorRed() {
	return this->red.get();
}

int Button::getColorGreen() {
	return this->green.get();
}

int Button::getColorBlue() {
	return this->blue.get();
}

bool Button::mouseMotion(int mouseX, int mouseY) {
	this->hasFocus = isBoundedToSDLRect(mouseX, mouseY, &this->normalrect);
	return this->hasFocus;
}

bool Button::leftMouseDown(int mouseX, int mouseY) {
	if (this->hasFocus) {
		this->down = true;
		return true;
	}
	return false;
}

bool Button::leftMouseUp(int mouseX, int mouseY) {
	this->down = false;
	return this->hasFocus;
}

void Button::update() {
	if (this->hasFocus) {
		if (!this->hadFocus) {
			this->red.goTo(COLOR.HOVER.r);
			this->green.goTo(COLOR.HOVER.g);
			this->blue.goTo(COLOR.HOVER.b);
		}
		this->red.update(20);
		this->green.update(20);
		this->blue.update(20);
	} else {
		if (this->hadFocus) {
			this->red.goTo(COLOR.FG.r);
			this->green.goTo(COLOR.FG.g);
			this->blue.goTo(COLOR.FG.b);
			this->red.fastForward();
			this->green.fastForward();
			this->blue.fastForward();
		}
	}

	this->hadFocus = this->hasFocus;
}
