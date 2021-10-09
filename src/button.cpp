#pragma once

#include "utils.cpp"

/*	button class (just a colored rect, the text/icon is handled separately)
*/

void noAction() {}

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
	void bindTo(void (*)());
private:
	SDL_Rect normalrect;
	SDL_Rect isDownrect;
	bool hasFocus;
	bool hadFocus;
	bool isDown;
	bool wasDown;
	AnimatedInt red;
	AnimatedInt green;
	AnimatedInt blue;
	void (*callback)();
};

void Button::init() {
	this->hasFocus = false;
	this->hadFocus = true;
	this->isDown = false;
	this->wasDown = true;
	// here hadFocus and wasDown are set to true so the color will be
	// initialised on the first `update` call
	this->callback = noAction;
}

void Button::place(int x, int y) {
	this->normalrect.x = x;
	this->normalrect.y = y;
	this->isDownrect.x = x+2;
	this->isDownrect.y = y+2; // buttons shrink when clicked

	this->hasFocus = isBoundedToSDLRect(lastKnownMouseX, lastKnownMouseY, &this->normalrect);
}

void Button::resize(int w, int h) {
	this->normalrect.w = w;
	this->normalrect.h = h;
	this->isDownrect.w = w-4;
	this->isDownrect.h = h-4; // see above
}

SDL_Rect *Button::getRect() {
	if (this->isDown) {
		return &this->isDownrect;
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
		this->isDown = true;
		return true;
	}
	return false;
}

bool Button::leftMouseUp(int mouseX, int mouseY) {
	this->isDown = false;
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
		this->blue.update(20); // fade to the selected color when gaining focus
		if (!this->isDown && this->wasDown) {
			this->callback();
		}
	} else {
		if (!this->isDown && (this->hadFocus || this->wasDown)) {
			this->red.goTo(COLOR.FG.r);
			this->green.goTo(COLOR.FG.g);
			this->blue.goTo(COLOR.FG.b);
			this->red.fastForward();
			this->green.fastForward();
			this->blue.fastForward(); // go back to the normal color instantly when losing focus
		}
	}

	this->hadFocus = this->hasFocus;
	this->wasDown = this->isDown;
}

void Button::bindTo(void (*function)()) {
	this->callback = function;
}