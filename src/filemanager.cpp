#pragma once

#include "utils.cpp"
#include <vector>

int openFilesCount;

struct File
{
	std::string name;
	std::string path;
};

std::vector<File> openFiles;

void updateOpenFilesCount() {
	openFilesCount = openFiles.size();
}