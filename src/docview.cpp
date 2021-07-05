#include "utils.cpp"
#include "button.cpp"

/*	Main view
*/

std::vector<SDL_Rect> documentTabRect;
SDL_Rect documentViewRect;

int startupcounter;

SDL_Rect noFileRect;
Button noFileBtn;

void documentViewInit() {
	documentViewRect.y = 95;
	mode = STARTUP;
	prevMode = STARTUP;
	startupcounter = 10;

	noFileBtn.init();
	noFileBtn.bindTo(createNewFile);
}

bool documentViewMouseMotion(int mouseX, int mouseY) {
	if (mode == NOFILE) {
		return noFileBtn.mouseMotion(mouseX, mouseY);
	}
	return false;
}

bool documentViewMouseDown(int btn, int mouseX, int mouseY) {
	if (mode == NOFILE) {
		if (btn==SDL_BUTTON_LEFT) {
			return noFileBtn.leftMouseDown(mouseX, mouseY);
		}
	}
	return false;
}

bool documentViewMouseUp(int btn, int mouseX, int mouseY) {
	if (mode == NOFILE) {
		if (btn == SDL_BUTTON_LEFT) {
			return noFileBtn.leftMouseUp(mouseX, mouseY);
		}
	}
	return false;
}

void documentViewUpdate() {
	switch (mode) {
	case STARTUP:
		// wait a little at startup
		if (startupcounter) {
			startupcounter --;
		} else {
			setMode(NOFILE);
		}
		break;

	case NOFILE:
		noFileRect.x = documentViewRect.x + documentViewRect.w/2 - noFileRect.w/2;
		noFileRect.y = documentViewRect.y + documentViewRect.h/2 - noFileRect.h/2;
		noFileBtn.place(
			noFileRect.x + noFileRect.w/2 - noFileBtn.getNormalRect()->w/2,
			noFileRect.y + noFileRect.h + 10 - noFileBtn.getNormalRect()->h  );
		noFileBtn.update();
		break;
	}

	if (mode != prevMode) {
		switch (prevMode) {
		case NOFILE:
			noFileRect.x = documentViewRect.x - 10 - documentViewRect.w/2 - noFileRect.w/2;
			noFileRect.y = documentViewRect.y + documentViewRect.h/2 - noFileRect.h/2;
			noFileBtn.place(
				noFileRect.x + noFileRect.w/2 - noFileBtn.getNormalRect()->w/2,
				noFileRect.y + noFileRect.h + 10 - noFileBtn.getNormalRect()->h  );
			noFileBtn.update();
			break;
		}
	}

	documentViewRect.x = getViewX()+10;
	documentViewRect.w = WIDTH-20;
	documentViewRect.h = HEIGHT-140;
}

SDL_Rect *documentViewGetRect() {
	return &documentViewRect;
}

void noFileTextureSize(int w, int h, int w2, int h2) {
	noFileRect.x = 0;
	noFileRect.y = -h; // hide by default
	noFileRect.w = w;
	noFileRect.h = h;
	noFileBtn.resize(w2+30, h2+20);
	noFileBtn.place(0, -h2-20); // same
}

SDL_Rect *noFileGetRect() {
	return &noFileRect;
}