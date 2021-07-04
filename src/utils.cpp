#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

int WIDTH, HEIGHT;

int RES_ICON = 0;
int RES_FONT = 1;
int RES_LANG = 2;

bool isBoundedToCoords(int x, int y, int x1, int y1, int x2, int y2) {
	if (x < x1) {
		return false;
	}
	if (x > x2) {
		return false;
	}
	if (y < y1) {
		return false;
	}
	if (y > y2) {
		return false;
	}
	return true;
}

bool isBoundedToRect(int x, int y, int x1, int y1, int w, int h) {
	return isBoundedToCoords(x, y, x1, y1, x1+w, y1+h);
}

bool isBoundedToSDLRect(int x, int y, SDL_Rect *rect) {
	return isBoundedToCoords(x, y, rect->x, rect->y, rect->x+rect->w, rect->y+rect->h);
}

std::string getResourcePath(int type, std::string resource) {
	if (type == RES_ICON) {
		return "res/icons/" + resource + ".png";
	}
	if (type == RES_FONT) {
		return "res/fonts/SourceSansPro-" + resource + ".ttf";
	}
	if (type == RES_LANG) {
		return "res/languages/" + resource + ".lang";
	}
	return "";
}

int mini(int a, int b) {return (a <= b) ? a : b;}

int maxi(int a, int b) {return (a >= b) ? a : b;}

float mapValue(float x, float fromMin, float fromMax, float toMin, float toMax) {
	return toMin+(((x-fromMin)/(fromMax-fromMin))*(toMax-toMin));
}

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
Uint32 rmask = 0xff000000;
Uint32 gmask = 0x00ff0000;
Uint32 bmask = 0x0000ff00;
Uint32 amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff;
Uint32 gmask = 0x0000ff00;
Uint32 bmask = 0x00ff0000;
Uint32 amask = 0xff000000;
#endif

std::string ERR = "\x1b[1;31m[ERROR] \x1b[0m";
std::string INF = "\x1b[1;34m[INFO ] \x1b[0m";

void logError(std::string errmsg, bool sdlerr) {
	if (sdlerr) {
		printf((ERR + errmsg + "\n").c_str(), SDL_GetError());
	} else {
		printf((ERR + errmsg + "\n").c_str());
	}
}

void logInfo(std::string errmsg) {
	printf((INF + errmsg + "\n").c_str());
}

#define DICTSIZE 20

std::string _LANG[DICTSIZE];

void loadLang(){
	std::fstream langfile;
	int i=0;

	for (int i=0; i<DICTSIZE; i++) {
		_LANG[i]="<LANG_" + std::to_string(i) + ">";
	}

	langfile.open(getResourcePath(RES_LANG, "en"), std::ios::in);
	if (langfile.is_open()) {
		while (getline(langfile, _LANG[i]) && (i+1)<DICTSIZE) {i++;}
		langfile.close();
	}
}

std::string getCaption(int i) {
	if (i >= DICTSIZE) {
		return "<LANG_" + std::to_string(i) + ">";
	} else {
		std::string a = _LANG[i];
		return _LANG[i];
	}
}

struct palette
{
	SDL_Color BG;
	SDL_Color FG;
	SDL_Color HOVER;
	SDL_Color TEXT;
};

palette COLOR = {
	{215, 215, 215, 255},
	{255, 255, 255, 255},
	{128, 192, 255, 255},
	{  0,   0,   0, 255},
};


class AnimatedInt
{
public:
	int get() {
		if (this->notCached) {
			this->notCached = false;
			this->cachedValue = mapValue(this->progress, 0, 100, this->start, this->end);
		}
		return this->cachedValue;
	};
	void goTo(int x) {
		this->start = this->get();
		this->end = x;
		this->progress = 0;
		this->notCached = true;
	};
	void update(int steps) {
		if (this->progress < 100) {
			this->progress += steps;
			if (this->progress > 100) {
				this->progress = 100;
			}
			this->notCached = true;
		}
	};
	void fastForward() {
		if (this->progress != 100) {
			this->progress = 100;
			this->notCached = true;
		}
	};
private:
	int progress;
	int start;
	int end;
	bool notCached;
	int cachedValue;
};

void createNewFile();

int mode;
int prevMode;
const int STARTUP = 0;
const int NOFILE = 1;
const int DOCUMENT = 2;
int _viewX = 0;

void setMode(int newMode) {
	if (newMode != mode) {
		mode = newMode;
		_viewX = WIDTH*10;
	}
}
int getViewX() {
	return _viewX/10;
}
void slideView() {
	if (_viewX > 5) {
		_viewX -= _viewX/5;
	} else if (_viewX > 0) {
		prevMode = mode;
		_viewX = 0;
	}
}