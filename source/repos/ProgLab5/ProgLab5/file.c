#include "main.h"

FILE *fFile = NULL, *fPrevFile = NULL;
char sPath[2048] = { '\0' };

void printCurrentLoadedFile()
{
	if (fFile == NULL)
	{
		printf("File: No file opened...\n\n");
		return;
	}

	printf("File: %s\n\n", sPath);
}

int tryToOpenFile(char *sInput)
{
	fPrevFile = fFile;
	fFile = fopen(sInput, "rb");

	if (fFile == NULL)
	{
		fFile = fPrevFile;
		return 0;
	}

	loadVectors(fFile);
	strcpy(sPath, sInput);
	return 1;
}

FILE* getCurrentFile()
{
	return fFile;
}