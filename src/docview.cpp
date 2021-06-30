#include "utils.cpp"

SDL_Rect documentViewRect;

SDL_Rect noFileRect;
SDL_Rect noFileBtnRect;
bool noFileBtnFocus = false;

void documentViewInit() {
	documentViewRect.x = 10;
	documentViewRect.y = 95;
}

bool documentViewMouseMotion(int mouseX, int mouseY) {
	if (openFilesCount) {

	} else {
		noFileBtnFocus = isBoundedToRect(mouseX, mouseY, &noFileBtnRect);
		return noFileBtnFocus;
	}
}

void documentViewUpdate(int W, int H) {
	documentViewRect.w = W-20;
	documentViewRect.h = H-140;
	if (openFilesCount) {

	} else {
		noFileRect.x = documentViewRect.x + documentViewRect.w/2 - noFileRect.w/2;
		noFileRect.y = documentViewRect.y + documentViewRect.h/2 - noFileRect.h/2;
		noFileBtnRect.x = noFileRect.x + noFileRect.w/2 - noFileBtnRect.w/2;
		noFileBtnRect.y = noFileRect.y + noFileRect.h + 10 - noFileBtnRect.h;
	}
}

SDL_Rect *documentViewGetRect(int i) {
	return &documentViewRect;
}

void noFileTextureSize(int w, int h, int w2, int h2) {
	noFileRect.w = w;
	noFileRect.h = h;
	noFileBtnRect.w = w2+30;
	noFileBtnRect.h = h2+20;
}

SDL_Rect *noFileGetRect() {
	return &noFileRect;
}

SDL_Rect *noFileGetBtnRect() {
	return &noFileBtnRect;
}

bool noFileFocused() {
	return noFileBtnFocus;
}