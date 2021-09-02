#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "languages.hpp"

/*	this is included everywhere
*/

// window size
int WIDTH, HEIGHT;

// resource type
const int RES_ICON = 0;
const int RES_FONT = 1;
const int RES_LANG = 2;

int LOGLVL;
const int QUIET = 0;
const int ERROR = 1;
const int INFO = 2;
const int DEBUG = 3;

int setup(int argc, char** args) {
	LOGLVL = ERROR;
	bool showHelp = false;
	bool showVersionInfo = false;

	int i = 1;
	while (i < argc) {
		if ((strcmp(args[i], "-Q") * strcmp(args[i], "--quiet")) == 0) {
			LOGLVL = QUIET;
		} else if ((strcmp(args[i], "-E") * strcmp(args[i], "--logerrors")) == 0) {
			LOGLVL = ERROR;
		} else if ((strcmp(args[i], "-I") * strcmp(args[i], "--loginfos")) == 0) {
			LOGLVL = INFO;
		} else if ((strcmp(args[i], "-D") * strcmp(args[i], "--debug")) == 0) {
			LOGLVL = DEBUG;
		} else if ((strcmp(args[i], "-h") * strcmp(args[i], "--help")) == 0) {
			showHelp = true;
		} else if ((strcmp(args[i], "-v") * strcmp(args[i], "--version")) == 0) {
			showVersionInfo = true;
		}
		i++;
	}

	if (showHelp) {
		printf("\n⣿⣿⣿⣿⣷⣄                 ⣿⣿");
		printf("\n⣿⣿ ⢈⣿⣿               ⣿⣿⣿⣿⣿⣿");
		printf("\n⣿⣿⣿⣿⣿⣏ ⣿⣿⣿⣿⣷⣄ ⣿⣿  ⣿⣿   ⣿⣿");
		printf("\n⣿⣿ ⢈⣿⣿ ⣿⣿⠁⠈⣿⣿ ⣿⣿⡀⢀⣿⣿   ⣿⣿⡀");
		printf("\n⣿⣿⣿⣿⡿⠋ ⣿⣿     ⠙⢿⣿⣿⣿⣿   ⠙⢿⣿⣿  V 1.0.0-DEV210902A\n");
		printf("\n~~~ Help on command line options ~~~\n");
		printf("\n-v, --version    display the version and exits");
		printf("\n-h, --help       display this message and exits\n");
		printf("\n-Q, --quiet      disable logs");
		printf("\n-E, --logerrors  log only errors (the default)");
		printf("\n-I, --loginfos   log information messages and errors");
		printf("\n-D, --debug      log everything\n");
		return 1;
	} else if (showVersionInfo) {
		printf("Brut (io.sourceforge.brut) version 1.0.0-dev210902A\n");
		return 1;
	}

	return 0;
}

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
		return "res/locale/" + resource + ".lang";
	}
	return "";
}

// doesn't these already exist in std ?
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
std::string DBG = "\x1b[1;36m[DEBUG] \x1b[0m";

void logError(std::string errmsg, bool sdlerr) {
	if (LOGLVL >= ERROR) {
		if (sdlerr) {
			printf((ERR + errmsg + "\n").c_str(), SDL_GetError());
		} else {
			printf((ERR + errmsg + "\n").c_str());
		}
	}
}

void logInfo(std::string msg) {
	if (LOGLVL >= INFO) {
		printf((INF + msg + "\n").c_str());
	}
}

void debugMsg(std::string msg) {
	if (LOGLVL >= DEBUG) {
		printf((DBG + msg + "\n").c_str());
	}
}

struct palette
{
	SDL_Color BG;
	SDL_Color FG;
	SDL_Color HOVER;
	SDL_Color TEXT;
	SDL_Color TAB;
};

palette COLOR = {
	{215, 215, 215, 255},
	{255, 255, 255, 255},
	{128, 192, 255, 255},
	{  0,   0,   0, 255},
	{160, 160, 160, 255},
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
void closeFile();

int view;
int lastView;
const int STARTUP = 0;
const int NOFILE = 1;
const int DOCUMENT = 2;
int _viewX = 0;
int _targetViewX = 0;
int _viewY = 0;
int _targetViewY = 0;
int viewX;
int viewY;

void switchToView(int newView) {
	if (newView != view) {
		view = newView;
	}
	if (lastView == STARTUP) {
		if (view == NOFILE) {
			_viewX = -1000;
			_viewY = -1000;
			_targetViewX = -1000;
			_targetViewY = 0;
		}
	}
}

bool MARKDOWN = false;
std::string NEWLINE = "\n";