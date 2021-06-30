#include "utils.cpp"
#include "filemanager.cpp"
#include <vector>

std::vector<SDL_Rect> fileTabsRects;

void fileTabsInit() {

}

bool fileTabsMouseMotion(int mouseX, int mouseY) {
	return false;
}

void fileTabsUpdate(int W, int H) {
	
}

SDL_Rect *fileTabsGetTabRect(int i) {
	return &fileTabsRects[i];
}