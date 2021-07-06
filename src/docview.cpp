#include "utils.cpp"
#include "button.cpp"
#include "filemanager.cpp"

#include <vector>

/*	Main view
*/

std::vector<SDL_Rect> documentTabRect;
std::vector<SDL_Rect> documentTabSrcRect;
std::vector<SDL_Rect> documentTabDstRect;
std::vector<SDL_Rect> documentTabIconRect; // fuck this there will be a max of opened docs at the same time
int documentTabsCount;
int selectedDocument;
SDL_Rect newDocumentRect;
SDL_Rect documentViewRect;

int startupcounter;

SDL_Rect noFileRect;
Button noFileBtn;

void documentViewInit() {
	documentViewRect.y = 95;
	newDocumentRect.x = -25;
	newDocumentRect.y = 70;
	newDocumentRect.h = 25;
	newDocumentRect.w = 25;
	mode = STARTUP;
	prevMode = STARTUP;
	startupcounter = 10;

	noFileBtn.init();
	noFileBtn.bindTo(createNewFile);

	documentTabsCount = 0;
	selectedDocument = -1;
}

bool documentViewMouseMotion(int mouseX, int mouseY) {
	switch (mode) {
	case NOFILE:
		return noFileBtn.mouseMotion(mouseX, mouseY);
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

	case DOCUMENT:
		if (documentTabsCount < openFilesCount) {
			documentTabRect.push_back({0, 70, 0, 25});
			documentTabsCount = documentTabRect.size();
			selectedDocument = documentTabsCount-1;
		}
		int x = getViewX()+10;
		for (int i=0; i<documentTabsCount; i++) {
			documentTabRect[i].x = x;
			documentTabRect[i].w = 200;
			x += documentTabRect[i].w + 4;
		}
		newDocumentRect.x = x;
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

SDL_Rect *newDocumentGetRect() {
	return &newDocumentRect;
}

void newDocnameTextureSize(int w, int h) {
	documentNameW.push_back(w);
	documentSrcRect.push_back({0, 0, 0, h});
	int padding = 12-h/2;
	documentDstRect.push_back({padding, padding, 0, h});
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