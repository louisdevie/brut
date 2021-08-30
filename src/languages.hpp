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

const int LANGERR_UNKNOWN = 1;
const int LANGERR_FAILEDTOOPEN = 2;
const int LANGERR_MISSINGFIELD = 3;

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
		if (i > 6) {
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