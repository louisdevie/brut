#pragma once

#include <string>
#include <vector>
#include <fstream>

struct _LANG_DSTR {
	std::string STR;
	std::string ADDINFO;
};

std::string _LANG_APP_ID;
std::string _LANG_CURRENT_UID;
std::string _LANG_CURRENT_NAME;
std::string _LANG_DECSEP;
std::string _LANG_LARGESEP;
std::vector<_LANG_DSTR> _LANG_RULES_NUM;
std::vector<std::string> _LANG_DAYS;
std::vector<std::string> _LANG_MONTHS;
std::vector<_LANG_DSTR> _LANG_RULES_DATE;
std::vector<_LANG_DSTR> _LANG_RULES_TIME;
std::vector<_LANG_DSTR> _LANG_RULES_SPAN;
std::vector<_LANG_DSTR> _LANG_APP_TEXT;
int _LANG_DICT_SIZE;

std::string *splitLine;
size_t splitNext;
size_t splitLast;
std::string splitResult;
void splitBegin(std::string *line) {
	splitLine = line;
	splitNext = 0;
	splitLast = 0;
}
bool split() {
	if ((splitNext = splitLine->find(_LANG_SEPCHAR, splitLast)) != std::string::npos) {
		splitResult = splitline->substr(splitLast, splitNext-splitLast);
		splitLast = splitNext+1;
		return true;
	} else {
		return false;
	}
}

const int LANGERR_UNKNOWN = 1;
const int LANGERR_FAILEDTOOPEN = 2;
const int LANGERR_MISSINGFIELD = 3;
const int LANGERR_FOREIGNAPP = 4;

void setAppID(std::string ID) {
	_LANG_APP_ID = ID;
}

int loadLanguage(std::string path) {
	std::fstream langFile;
	std::string buffer;
	int i = 0;

	langFile.open(path, std::ios::in);
	if (!langFile.is_open()) {
		return LANGERR_FAILEDTOOPEN;
	}
	
	while (getline(langFile, buffer)) {
		if (i == 0) {
			splitBegin(&buffer);
			if (!splitNext()) {return LANGERR_MISSINGFIELD;}
			if (_LANG_APP_ID && splitResult != _LANG_APP_ID) {return LANGERR_FOREIGNAPP;}
		} else if (i > 6) {
			_LANG_APP_TEXT.push_back({buffer, ""});
		}
		i++;
	}
	
	if (i<7) {
		return LANGERR_MISSINGFIELD;
	}

	_LANG_DICT_SIZE = _LANG_APP_TEXT.size();
	
	langFile.close();
	
	return 0;
}

std::string getCaption (int index) {
	if (index >= 0 && index < _LANG_DICT_SIZE) {
		return _LANG_APP_TEXT[index].STR;
	} else {
		return "<apptext-" + std::to_string(index) + ">";
	}
}