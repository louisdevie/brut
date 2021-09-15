#include "utils.cpp"
#include "parsers.cpp"

SDL_Surface *RENDERED_TEXT;
Uint32 greycolor;
SDL_Texture *RTEX;

TTF_Font *_chooseFont(int style) {
	return FONT_INTERFACE;
}

SDL_Color _chooseColor(int style) {
	return COLOR.TEXT;
}

void renderText(int framew, int scrollY, int frameH) {
	debugMsg("TEXT RENDERER: rendering text ...");
	std::string *text = &openFiles[selectedDocument].content;
	parseText(text);
	int result_size = RESULT.size();

	SDL_FillRect(RENDERED_TEXT, NULL, greycolor);
	SDL_Surface *surface;
	SDL_Rect dstrect;
	int x = 0;
	int y = 0;
	for (int i; i<result_size; i++) {
		_resultChunk chunk = RESULT[i];
		surface = TTF_RenderUTF8_Blended(
			_chooseFont(chunk.style),
			text->substr(chunk.start, chunk.span).c_str(),
			_chooseColor(chunk.style)
		);
		dstrect.w = surface->w;
		dstrect.h = surface->h;
		SDL_BlitSurface(surface, NULL, RENDERED_TEXT, &dstrect);
		SDL_FreeSurface(surface);
	}
}

int findLine(int y) {}
int findChunk(int line, int x) {}
int findChar(int line, int chunk, int x) {}