#include </usr/include/SDL2/SDL.h>
#include </usr/include/SDL2/SDL_ttf.h>
#include </usr/include/SDL2/SDL_image.h>

#include "menubar.cpp"
#include "docview.cpp"
#include "bottombar.cpp"
#include "utils.cpp"
#include "filemanager.cpp"

/*	SDL stuff, and brings everything together
*/

SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDERER = NULL;

TTF_Font *FONT_INTERFACE = NULL;
SDL_Surface *ICON_MISSING = NULL; //
SDL_Surface *ICON_MENUBAR[NTABS]; // temp
SDL_Surface *ICON_TAB[3];

SDL_Event event;

bool GUI_QUIT = false;

SDL_Texture *TEXTURE_MENUBAR[NTABS];
void drawMenuBar();

void drawFileTabs();

SDL_Texture *TEXTURE_NOFILE;
SDL_Texture *TEXTURE_TABICON[3];
SDL_Texture *TEXTURE_DOCNAME[MAXDOCS];
void drawDocumentView();

void drawBottomBar();

int GUI_Init()
{
	logInfo("GUI: initializing ...");
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "couldn't initialize SDL2: %s\n", SDL_GetError());
		return 1;
	}
	
	if(TTF_Init() < 0)
	{
		fprintf(stderr, "couldn't initialize SDL2_ttf: %s\n", SDL_GetError());
		return 1;
	}

	if(IMG_Init(IMG_INIT_PNG) < 0)
	{
		fprintf(stderr, "couldn't initialize SDL2_image: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}

void GUI_Quit()
{
	logInfo("GUI: exitting ...");

	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

void GUI_LoadResources() {
	logInfo("GUI: loading resources ...");

	FONT_INTERFACE = TTF_OpenFont(getResourcePath(RES_FONT, "Regular").c_str(), 18);
	if (!FONT_INTERFACE)
	{
		fprintf(stderr, "error loading font: %s", SDL_GetError());
	}

	ICON_MISSING = IMG_Load(getResourcePath(RES_ICON, "missing").c_str());
	if (!ICON_MISSING)
	{
		fprintf(stderr, "error loading fallback icon: %s", SDL_GetError());
		ICON_MISSING = SDL_CreateRGBSurface(0, 32, 32, 32, rmask, gmask, bmask, amask);
	}
	std::string icons[NTABS] = {"open", "clock", "save", "copy", "sliders", "info"};
	for (int i=0; i<NTABS; i++) {
		ICON_MENUBAR[i] = IMG_Load(getResourcePath(RES_ICON, icons[i]).c_str());
		if (!ICON_MENUBAR[i])
		{
			logError("error loading icon: %s", 1);
			ICON_MENUBAR[i] = SDL_CreateRGBSurface(0, 32, 32, 32, rmask, gmask, bmask, amask);
			SDL_BlitSurface(ICON_MISSING, NULL, ICON_MENUBAR[i], NULL); // use default icon instead
		}
	}
	SDL_Rect defaultrect = {-3, -3, 32, 32};
	std::string smallIcons[3] = {"small-plus", "small-cross", "small-dot"};
	for (int i=0; i<3; i++) {
		ICON_TAB[i] = IMG_Load(getResourcePath(RES_ICON, smallIcons[i]).c_str());
		if (!ICON_TAB[i])
		{
			logError("error loading icon: %s", 1);
			ICON_TAB[i] = SDL_CreateRGBSurface(0, 25, 25, 32, rmask, gmask, bmask, amask);
			SDL_BlitSurface(ICON_MISSING, NULL, ICON_TAB[i], &defaultrect); // use default icon instead
		}
	}

	loadLang();
}

void GUI_UnloadResources() {
	logInfo("GUI: unloading resources ...");

	TTF_CloseFont(FONT_INTERFACE); 

	SDL_FreeSurface(ICON_MISSING);
	for (int i=0; i<NTABS; i++) {
		SDL_FreeSurface(ICON_MENUBAR[i]);
	}
}

void GUI_GenerateTextures() {
	logInfo("GUI: generating textures ...");

	SDL_Rect rect1 = {0, 0, 32, 32};
	SDL_Rect rect2 = {42, 0, 32, 32};
	for (int i=0; i<NTABS; i++) {

		SDL_Surface *text = TTF_RenderUTF8_Blended(FONT_INTERFACE, getCaption(i).c_str(), COLOR.TEXT);
		rect2.y = 16 - text->h/2;
		rect2.w = text->w;
		rect2.h = text->h;

		SDL_Surface *surface = SDL_CreateRGBSurface(0, rect2.x+rect2.w, 32, 32, rmask, gmask, bmask, amask);

		SDL_BlitSurface(ICON_MENUBAR[i], NULL, surface, &rect1);
		SDL_BlitSurface(text, NULL, surface, &rect2);
		TEXTURE_MENUBAR[i] = SDL_CreateTextureFromSurface(RENDERER, surface);

		SDL_FreeSurface(surface);
		SDL_FreeSurface(text);

		menuBarTextureSize(i, rect2.x+rect2.w);
	}

	// info text
	SDL_Surface *nofilemsg = TTF_RenderUTF8_Blended(FONT_INTERFACE, getCaption(NTABS).c_str(), COLOR.TEXT);
	rect1.w = nofilemsg->w;
	rect1.h = nofilemsg->h;
	// button text
	SDL_Surface *nofilebtn = TTF_RenderUTF8_Blended(FONT_INTERFACE, getCaption(NTABS+1).c_str(), COLOR.TEXT);
	rect2.w = nofilebtn->w;
	rect2.h = nofilebtn->h;
	// group them together
	rect1.x = maxi(rect2.w-rect1.w, 0)/2;
	rect1.y = 0;
	rect2.x = maxi(rect1.w-rect2.w, 0)/2;
	rect2.y = rect1.h+40;
	SDL_Surface *nofilesurface = SDL_CreateRGBSurface(0, maxi(rect1.w, rect2.w), rect2.y+rect2.h, 32, rmask, gmask, bmask, amask);
	SDL_BlitSurface(nofilemsg, NULL, nofilesurface, &rect1);
	SDL_BlitSurface(nofilebtn, NULL, nofilesurface, &rect2);
	TEXTURE_NOFILE = SDL_CreateTextureFromSurface(RENDERER, nofilesurface);
	noFileTextureSize(nofilesurface->w, nofilesurface->h, rect2.w, rect2.h);
	SDL_FreeSurface(nofilemsg);
	SDL_FreeSurface(nofilebtn);
	SDL_FreeSurface(nofilesurface);

	for (int i=0; i<3; i++) {
		TEXTURE_TABICON[i] = SDL_CreateTextureFromSurface(RENDERER, ICON_TAB[i]);
		SDL_FreeSurface(ICON_TAB[i]);
	}
}

void GUI_DestroyTextures() {
	logInfo("GUI: destroying textures ...");
	
	for (int i=0; i<NTABS; i++) {
		SDL_DestroyTexture(TEXTURE_MENUBAR[i]);
	}

	SDL_DestroyTexture(TEXTURE_NOFILE);

	for (int i=0; i<3; i++) {
		SDL_DestroyTexture(TEXTURE_TABICON[i]);
	}

	for (int i=0; i<MAXDOCS; i++) {
		if (TEXTURE_DOCNAME[i]) {
			SDL_DestroyTexture(TEXTURE_DOCNAME[i]);
		}
	}
}

void GUI_OpenWindow() {
	logInfo("GUI: creating window ...");
	
	SDL_DisplayMode displayMode;
	if(SDL_GetDesktopDisplayMode(0, &displayMode) < 0)
	{
		fprintf(stderr, "SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
		WIDTH = 500;
		HEIGHT = 500;
	}
	else
	{
		WIDTH = displayMode.w/2;
		HEIGHT = displayMode.h/1.5; // fixed window size, but adapt to your screen
	}
	WINDOW = SDL_CreateWindow(
		"Brut.",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN
	);
	RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);
	SDL_SetRenderDrawColor(RENDERER, COLOR.BG.r, COLOR.BG.g, COLOR.BG.b, 255);
	SDL_RenderClear(RENDERER);

	menuBarInit();
	documentViewInit();
	bottomBarInit();
}

void GUI_CloseWindow() {
	logInfo("GUI: closing window ...");
	
	SDL_DestroyWindow(WINDOW);
	SDL_DestroyRenderer(RENDERER);
}

void GUI_HandleEvents()
{
	while (SDL_PollEvent(&event) > 0)
	{
		switch (event.type)
		{
			case SDL_QUIT:
				GUI_QUIT = true;
				break;

			case SDL_MOUSEMOTION:
				if (menuBarMouseMotion(event.motion.x, event.motion.y)) {break;}
				documentViewMouseMotion(event.motion.x, event.motion.y); break;

			case SDL_MOUSEBUTTONDOWN:
				documentViewMouseDown(event.button.button, event.button.x, event.button.y);	break;

			case SDL_MOUSEBUTTONUP:
				documentViewMouseUp(event.button.button, event.button.x, event.button.y);	break;
		}
	}
}

void GUI_UpdateWindow()
{
	SDL_SetRenderDrawColor(RENDERER, COLOR.BG.r, COLOR.BG.g, COLOR.BG.b, 255);
	SDL_RenderClear(RENDERER);

	slideView();

	menuBarUpdate();
	documentViewUpdate();
	bottomBarUpdate();

	drawMenuBar();
	drawDocumentView();
	drawBottomBar();

	SDL_RenderPresent(RENDERER);
	SDL_Delay(30);
}

void drawMenuBar() {
	int focused = menuBarFocused();
	for (int i=0; i<NTABS; i++) {
		if (i == focused) {
			SDL_SetRenderDrawColor(RENDERER, COLOR.HOVER.r, COLOR.HOVER.g, COLOR.HOVER.b, 255);
		} else {
			SDL_SetRenderDrawColor(RENDERER, COLOR.FG.r, COLOR.FG.g, COLOR.FG.b, 255);
		}
		SDL_Rect buttonRect = menuBarGetButtonRect(i);
		SDL_RenderFillRect(RENDERER, &buttonRect);
		SDL_RenderCopy(RENDERER, TEXTURE_MENUBAR[i], menuBarGetSrcRect(i), menuBarGetDstRect(i));
	}
}

void drawDocumentView() {
	switch (mode) {
	case NOFILE:
		SDL_SetRenderDrawColor(RENDERER, noFileBtn.getColorRed(), noFileBtn.getColorGreen(), noFileBtn.getColorBlue(), 255);
		SDL_RenderFillRect(RENDERER, noFileBtn.getRect());
		SDL_RenderCopy(RENDERER, TEXTURE_NOFILE, NULL, noFileGetRect());
		break;

	case DOCUMENT:
		SDL_SetRenderDrawColor(RENDERER, COLOR.TAB.r, COLOR.TAB.g, COLOR.TAB.b, 255);
		SDL_RenderFillRect(RENDERER, newDocumentGetRect());
		SDL_RenderCopy(RENDERER, TEXTURE_TABICON[0], NULL, newDocumentGetRect());
		for (int i=0; i<openFilesCount; i++) {
			if (i == selectedDocument) {
				SDL_SetRenderDrawColor(RENDERER, COLOR.FG.r, COLOR.FG.g, COLOR.FG.b, 255);
				SDL_RenderFillRect(RENDERER, getTabRect(i));
				SDL_RenderCopy(RENDERER, TEXTURE_DOCNAME[i], getTabSrcRect(i), getTabDstRect(i));		
				SDL_SetRenderDrawColor(RENDERER, closeTabBtn.getColorRed(), closeTabBtn.getColorGreen(), closeTabBtn.getColorBlue(), 255);
				SDL_RenderFillRect(RENDERER, closeTabBtn.getRect());
				SDL_RenderCopy(RENDERER, TEXTURE_TABICON[1], NULL, getTabIconRect(i));
			} else {
				SDL_SetRenderDrawColor(RENDERER, COLOR.TAB.r, COLOR.TAB.g, COLOR.TAB.b, 255);
				SDL_RenderFillRect(RENDERER, getTabRect(i));
				SDL_RenderCopy(RENDERER, TEXTURE_DOCNAME[i], getTabSrcRect(i), getTabDstRect(i));
				SDL_RenderCopy(RENDERER, TEXTURE_TABICON[1], NULL, getTabIconRect(i));
			}
		}
		SDL_SetRenderDrawColor(RENDERER, COLOR.FG.r, COLOR.FG.g, COLOR.FG.b, 255);
		SDL_RenderFillRect(RENDERER, documentViewGetRect());
		break;
	}
	if (mode != prevMode) {
		switch (prevMode) {
		case NOFILE:
			SDL_SetRenderDrawColor(RENDERER, COLOR.FG.r, COLOR.FG.g, COLOR.FG.b, 255);
			SDL_RenderFillRect(RENDERER, noFileBtn.getRect());
			SDL_RenderCopy(RENDERER, TEXTURE_NOFILE, NULL, noFileGetRect());
			break;

		case DOCUMENT:
			SDL_SetRenderDrawColor(RENDERER, COLOR.TAB.r, COLOR.TAB.g, COLOR.TAB.b, 255);
			SDL_RenderFillRect(RENDERER, newDocumentGetRect());
			SDL_RenderCopy(RENDERER, TEXTURE_TABICON[0], NULL, newDocumentGetRect());
			for (int i=0; i<openFilesCount; i++) {
				SDL_SetRenderDrawColor(RENDERER, COLOR.TAB.r, COLOR.TAB.g, COLOR.TAB.b, 255);
				SDL_RenderFillRect(RENDERER, getTabRect(i));
				SDL_RenderCopy(RENDERER, TEXTURE_DOCNAME[i], getTabSrcRect(i), getTabDstRect(i));
				SDL_RenderCopy(RENDERER, TEXTURE_TABICON[1], NULL, getTabIconRect(i));
			}
			SDL_SetRenderDrawColor(RENDERER, COLOR.FG.r, COLOR.FG.g, COLOR.FG.b, 255);
			SDL_RenderFillRect(RENDERER, documentViewGetRect());
			break;
		}
	}
}

void updateDocnameTexture(int i) {
	SDL_Surface *name = TTF_RenderUTF8_Blended(FONT_INTERFACE, openFiles[i].name.c_str(), COLOR.TEXT);
	docnameTextureSize(i, name->w, name->h);
	TEXTURE_DOCNAME[i] = SDL_CreateTextureFromSurface(RENDERER, name);
	SDL_FreeSurface(name);
}

void drawBottomBar() {

}