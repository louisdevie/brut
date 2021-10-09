#include "utils.cpp"

// use uint16_t instead ?
const int _STYLE_LINEEND = 1; // to indicate the chunk is the last of the line/paragraph
const int _STYLE_MARKUP = 2;
const int _STYLE_BOLD = 4;
const int _STYLE_ITALIC = 8;
const int _STYLE_UNDERLINE = 16;
const int _STYLE_CENTERED = 32;
const int _STYLE_TITLE = 64;   // four sizes of text :
const int _STYLE_SECTION = 128; // nothing, SECTION, SECTION+TITLE, TITLE
const int _STYLE_MONOSPACE = 256; // inline code / code block
const int _STYLE_QUOTE = 512;
const int _STYLE_AUTHOR = 1024; // quote author
const int _STYLE_LINK = 2048;
const int _STYLE_HIGHLIGHTED = 4096;

struct _resultChunk {
	size_t start;
	size_t span;
	int style;
};

std::vector<_resultChunk> RESULT;

void _parseMD(std::string *text) {}

void _parsePlain(std::string *text) {
	RESULT.clear();

	size_t next = 0;
	size_t last = 0;
	while ((next = text->find(NEWLINE, last)) != std::string::npos) {
		RESULT.push_back({last, next-last, _STYLE_LINEEND});
		last = next+1;
	}
	RESULT.push_back({last, next-last, 0});
}

void parseText(std::string *text) {
	if (MARKDOWN) {
		_parseMD(text);
	} else {
		_parsePlain(text);
	}
}