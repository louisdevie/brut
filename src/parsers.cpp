#include "utils.cpp"
#include "files.cpp"

// use unigned ints instead ?
const int _STYLE_LINEEND = 1; // to indicate line feed
const int _STYLE_MARKUP = 2;
const int _STYLE_BOLD = 4;
const int _STYLE_ITALIC = 8;
const int _STYLE_CENTERED = 16;
const int _STYLE_TITLE = 32;   // four sizes of text :
const int _STYLE_SECTION = 64; // nothing, SECTION, SECTION+TITLE, TITLE
const int _STYLE_MONOSPACE = 128; // inline code / code block
const int _STYLE_QUOTE = 256;
const int _STYLE_AUTHOR = 512; // quote block author
const int _STYLE_LINK = 1024;
const int _STYLE_HIGHLIGHTED = 2048;

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