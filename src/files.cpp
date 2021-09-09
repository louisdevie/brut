#pragma once

#include "utils.cpp"

#define MAXDOCS 10

/*	Manages files.
*/

int openFilesCount = 0;

struct File
{
	std::string name;
	std::string path;
	std::string content;
};

File openFiles[MAXDOCS];

int appendFile(File file) {
	openFiles[openFilesCount] = file;
	openFilesCount ++;
	return openFilesCount-1;
}

int removeFile(int file) {
	openFilesCount --;
	for (int i=file; i<openFilesCount; i++) {
		openFiles[i] = openFiles[i+1];
	};
	openFiles[openFilesCount] = {"", ""};

	if (file==0 && openFilesCount>1) {
		return file;
	} else {
		return file-1;
	}
}