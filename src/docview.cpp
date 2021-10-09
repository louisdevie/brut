#include "utils.cpp"
#include "button.cpp"
#include "files.cpp"

/*	document view
*/

SDL_Rect documentTabRect[MAXDOCS];
SDL_Rect documentTabSrcRect[MAXDOCS];
int documentTabTexW[MAXDOCS];
SDL_Rect documentTabDstRect[MAXDOCS];
SDL_Rect documentTabIconRect[MAXDOCS];
int documentTabPadding;
int selectedDocument;
bool textChanged;
SDL_Rect newDocumentRect;
Button closeTabBtn;

SDL_Rect documentRect;
SDL_Rect textRect;

void documentViewInit() {
	documentRect.x = -WIDTH;
	documentRect.y = 95;
	documentRect.w = WIDTH - 20;
	documentRect.h = HEIGHT - 105;
	textRect.x = -100;
	textRect.y = 105;
	textRect.w = 100;
	textRect.h = 100;
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

	closeTabBtn.init();
	closeTabBtn.resize(25, 25);
	closeTabBtn.place(0, -25);
	closeTabBtn.bindTo(closeFile);
}

bool documentViewMouseMotion(int mouseX, int mouseY) {
	if (view == DOCUMENT) {
		return closeTabBtn.mouseMotion(mouseX, mouseY);
	}
	return false;
}

bool documentViewMouseDown(int btn, int mouseX, int mouseY) {
	if (view == DOCUMENT) {
		if (btn == SDL_BUTTON_LEFT) {
			return closeTabBtn.leftMouseDown(mouseX, mouseY);
		}
	}
	return false;
}

bool documentViewMouseUp(int btn, int mouseX, int mouseY) {
	if (view == DOCUMENT) {
		if (btn == SDL_BUTTON_LEFT) {
			return closeTabBtn.leftMouseUp(mouseX, mouseY);
		}
	}
	return false;
}

void documentViewUpdate() {
	if (view == DOCUMENT xor lastView == DOCUMENT) {
		int x = 10 - viewX;
		documentRect.x = x;
		textRect.x = x+10;
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
			}
		}
		newDocumentRect.x = x;
	}
	if (view == DOCUMENT) {
		closeTabBtn.update();
		if (sizeChanged) {
			documentRect.w = WIDTH - 20;
			documentRect.h = HEIGHT - 105;
		}
	}
}

SDL_Rect *getDocumentRect() {
	return &documentRect;
}

SDL_Rect *newDocumentGetRect() {
	return &newDocumentRect;
}

SDL_Rect *getTextRect() {
	return &textRect;
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