#pragma once

#include <stdio.h>
#include <string>

int RES_ICON = 0;
int RES_FONT = 1;

bool isBoundedToCoords(int, int, int, int, int, int);
bool isBoundedToRect(int, int, int, int, int, int);

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

std::string getResourcePath(int type, std::string resource) {
	if (type == RES_ICON) {
		return "res/icons/" + resource + ".png";
	}
	if (type == RES_FONT) {
		return "res/fonts/SourceSansPro-" + resource + ".ttf";
	}
	return "";
}

int mini(int a, int b) {return (a <= b) ? a : b;}

int maxi(int a, int b) {return (a >= b) ? a : b;}

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