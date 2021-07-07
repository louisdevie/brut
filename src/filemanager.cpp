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
};

File openFiles[MAXDOCS];

int appendFile(File file) {
	openFiles[openFilesCount] = file;
	openFilesCount ++;
	return openFilesCount-1;
}