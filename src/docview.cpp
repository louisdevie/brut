#include "utils.cpp"
#include "button.cpp"
#include "filemanager.cpp"

/*	Main view (the file need to be renamed)
*/

SDL_Rect mainViewRect;

SDL_Rect documentTabRect[MAXDOCS];
SDL_Rect documentTabSrcRect[MAXDOCS];
int documentTabTexW[MAXDOCS];
SDL_Rect documentTabDstRect[MAXDOCS];
SDL_Rect documentTabIconRect[MAXDOCS];
int documentTabPadding;
int selectedDocument;
SDL_Rect documentRect;
SDL_Rect newDocumentRect;
Button closeTabBtn;

int startupcounter;

SDL_Rect noFileRect;
Button noFileBtn;

void documentViewInit() {
	mainViewRect.y = 70;
	documentRect.y = 95;
	newDocumentRect.x = -25;
	newDocumentRect.y = 70;
	newDocumentRect.h = 25;
	newDocumentRect.w = 25;
	for (int i=0; i<MAXDOCS; i++) {
		documentTabRect[i].y = 70;
		documentTabRect[i].h = 25;
		documentTabIconRect[i].x = -25;
		documentTabIconRect[i].y = 70;
		documentTabIconRect[i].w = 25;
		documentTabIconRect[i].h = 25;
	}
	mode = STARTUP;
	prevMode = STARTUP;
	startupcounter = 10;

	closeTabBtn.init();
	closeTabBtn.resize(25, 25);
	closeTabBtn.place(0, -25);
	closeTabBtn.bindTo(closeFile);

	noFileBtn.init();
	noFileBtn.bindTo(createNewFile);

	selectedDocument = -1;
}

bool documentViewMouseMotion(int mouseX, int mouseY) {
	switch (mode) {
	case NOFILE:
		return noFileBtn.mouseMotion(mouseX, mouseY);

	case DOCUMENT:
		return closeTabBtn.mouseMotion(mouseX, mouseY);
	}
	return false;
}

bool documentViewMouseDown(int btn, int mouseX, int mouseY) {
	switch (mode) {
	case NOFILE:
		if (btn == SDL_BUTTON_LEFT) {
			return noFileBtn.leftMouseDown(mouseX, mouseY);
		}
		break;

	case DOCUMENT:
		if (btn == SDL_BUTTON_LEFT) {
			return closeTabBtn.leftMouseDown(mouseX, mouseY);
		}
		break;
	}
	return false;
}

bool documentViewMouseUp(int btn, int mouseX, int mouseY) {
	switch (mode) {
	case NOFILE:
		if (btn == SDL_BUTTON_LEFT) {
			return noFileBtn.leftMouseUp(mouseX, mouseY);
		}
		break;

	case DOCUMENT:
		if (btn == SDL_BUTTON_LEFT) {
			return closeTabBtn.leftMouseUp(mouseX, mouseY);
		}
		break;
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
		noFileRect.x = mainViewRect.x + mainViewRect.w/2 - noFileRect.w/2;
		noFileRect.y = mainViewRect.y + mainViewRect.h/2 - noFileRect.h/2;
		noFileBtn.place(
			noFileRect.x + noFileRect.w/2 - noFileBtn.getNormalRect()->w/2,
			noFileRect.y + noFileRect.h + 10 - noFileBtn.getNormalRect()->h  );
		noFileBtn.update();
		break;

	case DOCUMENT:
		int x = getViewX()+10;
		documentRect.x = x;
		documentRect.w = mainViewRect.w;
		documentRect.h = mainViewRect.h;
		for (int i=0; i<openFilesCount; i++) {
			documentTabRect[i].x = x;
			documentTabRect[i].w = 200;
			documentTabSrcRect[i].w = mini(170-documentTabPadding, documentTabTexW[i]);
			documentTabDstRect[i].x = x+documentTabPadding+5;
			documentTabDstRect[i].w = documentTabSrcRect[i].w;
			documentTabIconRect[i].x = x+175;
			x += 204;
			if (i == selectedDocument) {
				closeTabBtn.place(x-29, 70);
				closeTabBtn.update();
			}
		}
		newDocumentRect.x = x;
		break;
	}

	if (mode != prevMode) {
		switch (prevMode) {
		case NOFILE:
			noFileRect.x = mainViewRect.x - 10 - mainViewRect.w/2 - noFileRect.w/2;
			noFileRect.y = mainViewRect.y + mainViewRect.h/2 - noFileRect.h/2;
			noFileBtn.place(
				noFileRect.x + noFileRect.w/2 - noFileBtn.getNormalRect()->w/2,
				noFileRect.y + noFileRect.h + 10 - noFileBtn.getNormalRect()->h  );
			noFileBtn.update();
			break;

		case DOCUMENT:
			int x = getViewX()-10-mainViewRect.w;
			documentRect.x = x;
			documentRect.w = mainViewRect.w;
			documentRect.h = mainViewRect.h;
			for (int i=0; i<openFilesCount; i++) {
				documentTabRect[i].x = x;
				documentTabRect[i].w = 200;
				documentTabSrcRect[i].w = mini(170-documentTabPadding, documentTabTexW[i]);
				documentTabDstRect[i].x = x+documentTabPadding+5;
				documentTabDstRect[i].w = documentTabSrcRect[i].w;
				documentTabIconRect[i].x = x+175;
				x += 204;
			}
			newDocumentRect.x = x;
			break;
		}
	}

	mainViewRect.x = getViewX()+10;
	mainViewRect.w = WIDTH-20;
	mainViewRect.h = HEIGHT-115;
}

SDL_Rect *documentViewGetRect() {
	return &documentRect;
}

SDL_Rect *newDocumentGetRect() {
	return &newDocumentRect;
}

void docnameTextureSize(int i, int w, int h) {
	documentTabTexW[i] = w;
	if (documentTabSrcRect[0].h == 0) {
		documentTabPadding = 12-h/2;
		for (i=0; i<MAXDOCS; i++) {
			documentTabSrcRect[i].h = h;
			documentTabDstRect[i].y = 70+documentTabPadding;
			documentTabDstRect[i].h = h;
		}
	}
}

SDL_Rect *getTabRect(int i) {
	return &documentTabRect[i];
}

SDL_Rect *getTabSrcRect(int i) {
	return &documentTabSrcRect[i];
}

SDL_Rect *getTabDstRect(int i) {
	return &documentTabDstRect[i];
}

SDL_Rect *getTabIconRect(int i) {
	return &documentTabIconRect[i];
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