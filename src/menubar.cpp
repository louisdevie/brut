#include "utils.cpp"

#define NTABS 6

SDL_Rect menuBarButtonRects[NTABS];
int menuBarTexSize[NTABS];
SDL_Rect menuBarTexSrc[NTABS];
SDL_Rect menuBarTexDst[NTABS];
int menuBarFocus;

void menuBarInit() {
	menuBarFocus = -1;

	for (int i=0; i<NTABS; i++) {
		menuBarButtonRects[i].y = 10;
		menuBarButtonRects[i].h = 50;
		menuBarTexSrc[i].x = 0;
		menuBarTexSrc[i].y = 0;
	}
}

bool menuBarMouseMotion(int mouseX, int mouseY) {
	menuBarFocus = -1;
	for (int i=0; i<NTABS; i++) {
		if (isBoundedToRect(mouseX, mouseY, &menuBarButtonRects[i])) {
			menuBarFocus = i;
			return true;
		}
	}
	return false;
}

void menuBarUpdate(int W, int H) {
	if (menuBarFocus == -1) {
		for (int i=0; i<NTABS; i++) {
			menuBarButtonRects[i].x = 10+((W-20)/NTABS)*i;
			menuBarButtonRects[i].w = (W-20)/NTABS;
			menuBarTexSrc[i].w = 32;
			menuBarTexDst[i].x = menuBarButtonRects[i].x + menuBarButtonRects[i].w/2 - 16;
			menuBarTexDst[i].w = 32;
		}
	} else {
		for (int i=0; i<NTABS; i++) {
			if (i == menuBarFocus) {
				menuBarButtonRects[i].x = 10+80*i;
				menuBarButtonRects[i].w = W+60-(80*NTABS);
				menuBarTexSrc[i].w = menuBarTexSize[i];
				menuBarTexDst[i].x = menuBarButtonRects[i].x + menuBarButtonRects[i].w/2 - menuBarTexSize[i]/2;
				menuBarTexDst[i].w = menuBarTexSize[i];
			} else {
				if (i < menuBarFocus) {
					menuBarButtonRects[i].x = 10+80*i;
					menuBarButtonRects[i].w = 80;
				} else {
					menuBarButtonRects[i].x = W-10-(80*(NTABS-i));
					menuBarButtonRects[i].w = 80;
				}
				menuBarTexSrc[i].w = 32;
				menuBarTexDst[i].x = menuBarButtonRects[i].x + menuBarButtonRects[i].w/2 - 16;
				menuBarTexDst[i].w = 32;
			}
		}
	}
}

SDL_Rect *menuBarGetButtonRect(int i) {
	return &menuBarButtonRects[i];
}

void menuBarTextureSize(int i, int w) {
	menuBarTexSize[i] = w;

	menuBarTexSrc[i].h = 32;
	menuBarTexDst[i].h = 32;
	menuBarTexDst[i].y = menuBarButtonRects[i].y + menuBarButtonRects[i].h/2 - 16;
}

SDL_Rect *menuBarGetSrcRect(int i) {
	return &menuBarTexSrc[i];
}

SDL_Rect *menuBarGetDstRect(int i) {
	return &menuBarTexDst[i];
}

int menuBarFocused() {
	return menuBarFocus;
}