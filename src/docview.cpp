#include "utils.cpp"
#include "button.cpp"

SDL_Rect documentViewRect;

SDL_Rect noFileRect;
Button noFileBtn;

void documentViewInit() {
	documentViewRect.x = 10;
	documentViewRect.y = 95;

	noFileBtn.init();
}

bool documentViewMouseMotion(int mouseX, int mouseY) {
	if (openFilesCount) {
		return false;
	} else {
		return noFileBtn.mouseMotion(mouseX, mouseY);
	}
}

bool documentViewMouseDown(int btn, int mouseX, int mouseY) {
	if (openFilesCount) {

	} else {
		if (btn==SDL_BUTTON_LEFT) {
			return noFileBtn.leftMouseDown(mouseX, mouseY);
		}
	}
	return false;
}

bool documentViewMouseUp(int btn, int mouseX, int mouseY) {
	if (openFilesCount) {

	} else {
		if (btn == SDL_BUTTON_LEFT) {
			return noFileBtn.leftMouseUp(mouseX, mouseY);
		}
	}
	return false;
}

void documentViewUpdate(int W, int H) {
	documentViewRect.w = W-20;
	documentViewRect.h = H-140;
	if (openFilesCount) {

	} else {
		noFileRect.x = documentViewRect.x + documentViewRect.w/2 - noFileRect.w/2;
		noFileRect.y = documentViewRect.y + documentViewRect.h/2 - noFileRect.h/2;
		noFileBtn.place(
			noFileRect.x + noFileRect.w/2 - noFileBtn.getNormalRect()->w/2,
			noFileRect.y + noFileRect.h + 10 - noFileBtn.getNormalRect()->h  );
		noFileBtn.update();
	}
}

SDL_Rect *documentViewGetRect(int i) {
	return &documentViewRect;
}

void noFileTextureSize(int w, int h, int w2, int h2) {
	noFileRect.w = w;
	noFileRect.h = h;
	noFileBtn.resize(w2+30, h2+20);
}

SDL_Rect *noFileGetRect() {
	return &noFileRect;
}