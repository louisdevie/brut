#include </usr/include/SDL2/SDL.h>
#include </usr/include/SDL2/SDL_ttf.h>
#include <stdio.h>

SDL_Window *WINDOW = NULL;
SDL_Renderer* RENDERER = NULL;
int WIDTH, HEIGHT;

SDL_Event event;

bool GUI_QUIT = false;

struct palette
{
	SDL_Color BG;
};

palette COLOR = {
	{230, 230, 230, 255},
};

int GUI_Init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "couldn't initialize SDL2: %s\n", SDL_GetError());
		return 1;
	}
	//TTF_Init();
	return 0;
}

void GUI_Quit()
{
	SDL_Quit();
	//TTF_Quit();
}

void GUI_OpenWindow()
{
	SDL_DisplayMode displayMode;
	if(SDL_GetDesktopDisplayMode(0, &displayMode) < 0)
	{
		fprintf(stderr, "SDL_GetDesktopDisplayMode failed: %s\n", SDL_GetError());
		WIDTH = 600;
		HEIGHT = 500;
	}
	else
	{
		WIDTH = displayMode.w/2;
		HEIGHT = displayMode.h/2;
	}
	WINDOW = SDL_CreateWindow(
		"Brut.",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN
	);
	RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);
}

void GUI_CloseWindow()
{
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
		}
	}
}

void GUI_UpdateWindow()
{
	SDL_SetRenderDrawColor(RENDERER, COLOR.BG.r, COLOR.BG.g, COLOR.BG.b, 255);
	SDL_RenderClear(RENDERER);
	SDL_RenderPresent(RENDERER);
	SDL_Delay(30);
}
/*
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window *window = SDL_CreateWindow(
		"Brut.",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		600,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	TTF_Font* font = TTF_OpenFont("SourceSansPro-Regular.ttf", 16);
	SDL_Color fore = {  0,   0,   0};
	SDL_Color back = {255, 255, 255};
	SDL_Surface * surface = TTF_RenderUTF8_Shaded(font, "Fichier", fore, back);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };

	SDL_Event input;

	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&input) > 0)
		{
			if (input.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
		SDL_Delay(30);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
	*/