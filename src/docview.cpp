#include "utils.cpp"

SDL_Rect documentViewRect;

SDL_Rect noFileRect;
SDL_Rect noFileBtnRect;
bool noFileBtnFocus;
bool noFileBtnPrevFocus;
AnimatedInt noFileBtnRed;
AnimatedInt noFileBtnGreen;
AnimatedInt noFileBtnBlue;

void documentViewInit() {
	documentViewRect.x = 10;
	documentViewRect.y = 95;

	noFileBtnFocus = false;
	noFileBtnPrevFocus = true;
}

bool documentViewMouseMotion(int mouseX, int mouseY) {
	if (openFilesCount) {

	} else {
		noFileBtnFocus = isBoundedToSDLRect(mouseX, mouseY, &noFileBtnRect);
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

		if (noFileBtnFocus) {
			if (!noFileBtnPrevFocus) {
				noFileBtnRed.goTo(COLOR.HOVER.r);
				noFileBtnGreen.goTo(COLOR.HOVER.g);
				noFileBtnBlue.goTo(COLOR.HOVER.b);
			}
			noFileBtnRed.update(20);
			noFileBtnGreen.update(20);
			noFileBtnBlue.update(20);
		} else {
			if (noFileBtnPrevFocus) {
				noFileBtnRed.goTo(COLOR.FG.r);
				noFileBtnGreen.goTo(COLOR.FG.g);
				noFileBtnBlue.goTo(COLOR.FG.b);
			}
			noFileBtnRed.fastForward();
			noFileBtnGreen.fastForward();
			noFileBtnBlue.fastForward();
		}

		noFileBtnPrevFocus = noFileBtnFocus;
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