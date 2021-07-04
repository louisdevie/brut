#include "utils.cpp"

/*	Bottom bar wich (will) show the number fo words and have few settings such
	as formatting or language 

	doesn't do anything for now
*/

SDL_Rect bottomBarRect;

void bottomBarInit() {
	bottomBarRect.x = 10;
	bottomBarRect.y = 95;
}

//TODO: remove parameters and use directly WDTH and HEIGHT instead
void bottomBarMouseMotion(int mouseX, int mouseY) {
	
}

void bottomBarUpdate(int W, int H) {
	bottomBarRect.w = W-20;
	bottomBarRect.h = H-140;
}

SDL_Rect *bottomBarGetRect(int i) {
	return &bottomBarRect;
}