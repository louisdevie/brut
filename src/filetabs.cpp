#include "utils.cpp"
#include "filemanager.cpp"
#include <vector>

/*	This should be handled by docview
*/

std::vector<SDL_Rect> fileTabsRects;

void fileTabsInit() {

}

//TODO: remove parameters and use directly WDTH and HEIGHT instead
bool fileTabsMouseMotion(int mouseX, int mouseY) {
	return false;
}

void fileTabsUpdate(int W, int H) {
	
}

SDL_Rect *fileTabsGetTabRect(int i) {
	return &fileTabsRects[i];
}