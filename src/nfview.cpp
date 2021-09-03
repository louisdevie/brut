#include "utils.cpp"
#include "button.cpp"

/*	welcome view if no documents are open
*/

SDL_Rect noFileRect;
Button noFileBtn;

void noFileViewInit() {
	noFileBtn.init();
	noFileBtn.bindTo(createNewFile);
}

bool noFileViewMouseMotion(int mouseX, int mouseY) {
	if (view == NOFILE) {
		return noFileBtn.mouseMotion(mouseX, mouseY);
	}
	return false;
}

bool noFileViewMouseDown(int btn, int mouseX, int mouseY) {
	if (view == NOFILE) {
		if (btn == SDL_BUTTON_LEFT) {
			return noFileBtn.leftMouseDown(mouseX, mouseY);
		}
	}
	return false;
}

bool noFileViewMouseUp(int btn, int mouseX, int mouseY) {
	if (view == NOFILE) {
		if (btn == SDL_BUTTON_LEFT) {
			return noFileBtn.leftMouseUp(mouseX, mouseY);
		}
	}
	return false;
}

void noFileViewUpdate() {
	if (view == NOFILE) {
		noFileRect.x = - WIDTH/2 - noFileRect.w/2 - viewX;
		noFileRect.y = 30 + HEIGHT/2 - noFileRect.h/2 - viewY;
		noFileBtn.place(
			noFileRect.x + noFileRect.w/2 - noFileBtn.getNormalRect()->w/2,
			noFileRect.y + noFileRect.h + 10 - noFileBtn.getNormalRect()->h);
		noFileBtn.update();
	}
	/*
	if (mode != prevMode) {
		if (lastView == NOFILE) {
			noFileRect.x = mainViewRect.x - 10 - mainViewRect.w/2 - noFileRect.w/2;
			noFileRect.y = mainViewRect.y + mainViewRect.h/2 - noFileRect.h/2;
			noFileBtn.place(
				noFileRect.x + noFileRect.w/2 - noFileBtn.getNormalRect()->w/2,
				noFileRect.y + noFileRect.h + 10 - noFileBtn.getNormalRect()->h  );
			noFileBtn.update();
		}
	}
	*/
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