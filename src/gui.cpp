#include </usr/include/SDL2/SDL.h>
#include </usr/include/SDL2/SDL_ttf.h>
#include </usr/include/SDL2/SDL_image.h>

#include "menubar.cpp"

SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDERER = NULL;
int WIDTH, HEIGHT;

TTF_Font *FONT_INTERFACE;
SDL_Surface *ICON_MISING;
SDL_Surface *ICON_OPEN;

SDL_Event event;

bool GUI_QUIT = false;

struct palette
{
	SDL_Color BG;
	SDL_Color FG;
	SDL_Color SEL;
	SDL_Color TEXT;
};

palette COLOR = {
	{230, 230, 230, 255},
	{255, 255, 255, 255},
	{128, 192, 255, 255},
	{  0,   0,   0, 255},
};

MenuBar UI_MENUBAR;
SDL_Texture *TEXTURE_MENUBAR[NTABS];
void drawMenuBar();

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

	ICON_MISING = IMG_Load(getResourcePath(RES_ICON, "missing").c_str());
	if (!ICON_MISING)
	{
		fprintf(stderr, "error loading fallback icon: %s", SDL_GetError());
		ICON_MISING = SDL_CreateRGBSurface(0, 32, 32, 32, rmask, gmask, bmask, amask);
	}
	ICON_OPEN = IMG_Load(getResourcePath(RES_ICON, "open").c_str());
	if (!ICON_OPEN)
	{
		logError("error loading icon \"OPEN\": %s", 1);
		ICON_OPEN = SDL_CreateRGBSurface(0, 32, 32, 32, rmask, gmask, bmask, amask);
		SDL_BlitSurface(ICON_MISING, NULL, ICON_OPEN, NULL);
	}
}

void GUI_UnloadResources() {
	logInfo("GUI: unloading resources ...");

	TTF_CloseFont(FONT_INTERFACE); 

	SDL_FreeSurface(ICON_MISING);
	SDL_FreeSurface(ICON_OPEN);
}

void GUI_GenerateTextures() {
	logInfo("GUI: generating textures ...");
	
	int texW = 0;
	SDL_Rect iconPos = {0, 0, 32, 32};
	SDL_Rect textPos = {42, 0, 32, 32};
	for (int i=0; i<NTABS; i++) {

		SDL_Surface *text = TTF_RenderUTF8_Blended(FONT_INTERFACE, "Tab", COLOR.TEXT);
		textPos.y = 16 - text->h/2;
		textPos.w = text->w;
		textPos.h = text->h;

		SDL_Surface *surface = SDL_CreateRGBSurface(0, textPos.x+textPos.w, 32, 32, rmask, gmask, bmask, amask);

		SDL_BlitSurface(ICON_OPEN, NULL, surface, &iconPos);
		SDL_BlitSurface(text, NULL, surface, &textPos);
		TEXTURE_MENUBAR[i] = SDL_CreateTextureFromSurface(RENDERER, surface);

		SDL_FreeSurface(surface);
		SDL_FreeSurface(text);

		SDL_QueryTexture(TEXTURE_MENUBAR[i], NULL, NULL, &texW, NULL);
		UI_MENUBAR.textureSize(i, texW);
	}
}

void GUI_DestroyTextures() {
	logInfo("GUI: destroying textures ...");
	
	for (int i=0; i<NTABS; i++) {
		SDL_DestroyTexture(TEXTURE_MENUBAR[i]);
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
		HEIGHT = displayMode.h/1.5;
	}
	WINDOW = SDL_CreateWindow(
		"Brut.",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN
	);
	RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);
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
			case SDL_QUIT: GUI_QUIT = true;

			case SDL_MOUSEMOTION: UI_MENUBAR.mouseMotion(event.motion.x, event.motion.y);
		}
	}
}

void GUI_UpdateWindow()
{
	SDL_SetRenderDrawColor(RENDERER, COLOR.BG.r, COLOR.BG.g, COLOR.BG.b, 255);
	SDL_RenderClear(RENDERER);

	UI_MENUBAR.update(WIDTH, HEIGHT);

	drawMenuBar();

	SDL_RenderPresent(RENDERER);
	SDL_Delay(30);
}

void drawMenuBar() {
	int focused = UI_MENUBAR.focused();
	for (int i=0; i<NTABS; i++) {
		if (i == focused) {
			SDL_SetRenderDrawColor(RENDERER, COLOR.SEL.r, COLOR.SEL.g, COLOR.SEL.b, 255);
		} else {
			SDL_SetRenderDrawColor(RENDERER, COLOR.FG.r, COLOR.FG.g, COLOR.FG.b, 255);
		}
		SDL_RenderFillRect(RENDERER, UI_MENUBAR.getTabRect(i));
		SDL_RenderCopy(RENDERER, TEXTURE_MENUBAR[i], UI_MENUBAR.getSrcRect(i), UI_MENUBAR.getDstRect(i));
	}
}
