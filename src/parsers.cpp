#pragma once

#include "utils.cpp"
#include "files.cpp"

const int _FORMAT_NONE = 0;
const int _FORMAT_LINEEND = 1;

struct _resultChunk {
	std::string text;
	int format;
};

std::vector<_resultChunk> RESULT;

void _parseMD(std::string *text) {}

void _parsePlain(std::string *text) {
	RESULT.clear();

	size_t pos;
	size_t last = 0;
	while ((pos = text->find(NEWLINE, last)) != std::string::npos) {
		RESULT.push_back({text->substr(last, pos-last), _FORMAT_LINEEND});
		last = pos+1;
	}
	RESULT.push_back({text->substr(last, pos-last), _FORMAT_NONE});
}

void parseText(int file) {
	if (MARKDOWN) {
		_parseMD(&openFiles[file].content);
	} else {
		_parsePlain(&openFiles[file].content);
	}
}