#include "utils.cpp"

SDL_Rect bottomBarRect;

void bottomBarInit() {
	bottomBarRect.x = 10;
	bottomBarRect.y = 95;
}

void bottomBarMouseMotion(int mouseX, int mouseY) {
	
}

void bottomBarUpdate(int W, int H) {
	bottomBarRect.w = W-20;
	bottomBarRect.h = H-140;
}

SDL_Rect *bottomBarGetRect(int i) {
	return &bottomBarRect;
}