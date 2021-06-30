#pragma once

#include "utils.cpp"
#include <vector>

int openFilesCount;

class File
{

};

std::vector<File> openFiles;

void updateOpenFilesCount() {
	openFilesCount = openFiles.size();
}