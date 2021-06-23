#include "utils.cpp"

#define NTABS 5

class MenuBar {
public:
	MenuBar();
	void mouseMotion(int, int);
	void update(int, int);
	SDL_Rect *getTabRect(int);
	void textureSize(int, int);
	SDL_Rect *getSrcRect(int);
	SDL_Rect *getDstRect(int);
	int focused();
private:
	SDL_Rect _tabRects[NTABS];
	int _texsize[NTABS];
	SDL_Rect _texsrc[NTABS];
	SDL_Rect _texdst[NTABS];
	int _focus;
};

MenuBar::MenuBar() {
	this->_focus = -1;

	for (int i=0; i<NTABS; i++) {
		this->_tabRects[i].y = 10;
		this->_tabRects[i].h = 50;
		this->_texsrc[i].x = 0;
		this->_texsrc[i].y = 0;
	}
}

void MenuBar::mouseMotion(int mouseX, int mouseY) {
	this->_focus = -1;
	for (int i=0; i<NTABS; i++) {
		if (isBoundedToRect(mouseX, mouseY,
							this->_tabRects[i].x,
							this->_tabRects[i].y,
							this->_tabRects[i].w,
							this->_tabRects[i].h)) {
			this->_focus = i;
			break;
		}
	}
}

void MenuBar::update(int W, int H) {
	if (this->_focus == -1) {
		for (int i=0; i<NTABS; i++) {
			this->_tabRects[i].x = 10+((W-20)/NTABS)*i;
			this->_tabRects[i].w = (W-20)/NTABS;
			this->_texsrc[i].w = 32;
			this->_texdst[i].x = this->_tabRects[i].x + this->_tabRects[i].w/2 - 16;
			this->_texdst[i].w = 32;
		}
	} else {
		for (int i=0; i<NTABS; i++) {
			if (i == this->_focus) {
				this->_tabRects[i].x = 10+80*i;
				this->_tabRects[i].w = W+60-(80*NTABS);
				this->_texsrc[i].w = this->_texsize[i];
				this->_texdst[i].x = this->_tabRects[i].x + this->_tabRects[i].w/2 - this->_texsize[i]/2;
				this->_texdst[i].w = this->_texsize[i];
			} else {
				if (i < this->_focus) {
					this->_tabRects[i].x = 10+80*i;
					this->_tabRects[i].w = 80;
				} else {
					this->_tabRects[i].x = W-10-(80*(NTABS-i));
					this->_tabRects[i].w = 80;
				}
				this->_texsrc[i].w = 32;
				this->_texdst[i].x = this->_tabRects[i].x + this->_tabRects[i].w/2 - 16;
				this->_texdst[i].w = 32;
			}
		}
	}
}

SDL_Rect *MenuBar::getTabRect(int i) {
	return &this->_tabRects[i];
}

void MenuBar::textureSize(int i, int w) {
	this->_texsize[i] = w;

	this->_texsrc[i].h = 32;
	this->_texdst[i].h = 32;
	this->_texdst[i].y = this->_tabRects[i].y + this->_tabRects[i].h/2 - 16;
}

SDL_Rect *MenuBar::getSrcRect(int i) {
	return &this->_texsrc[i];
}

SDL_Rect *MenuBar::getDstRect(int i) {
	return &this->_texdst[i];
}

int MenuBar::focused() {
	return this->_focus;
}