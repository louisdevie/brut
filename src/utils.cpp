#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

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

bool isBoundedToRect(int x, int y, SDL_Rect *rect) {
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
	SDL_Color SEL;
	SDL_Color TEXT;
};