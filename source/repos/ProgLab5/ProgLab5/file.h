#pragma once

#include "vector.h"

#define TEMP_PATH "C:\\Users\\Jake\\lab5.tmp"
#define OUT_PATH "C:\\Users\\Jake\\lab5out.vct"

void printCurrentLoadedFile();
int tryToOpenFile(char *sInput);

FILE* getCurrentFile();