#pragma once

#include <stdio.h>
#include <time.h>

#define MAX_VECTOR_SIZE (size_t)16
#define MAX_VECTOR_NAME 72

typedef struct
{
	size_t iSize;
	int64_t iCell[MAX_VECTOR_SIZE];
	char sName[MAX_VECTOR_NAME];
} vector_t;

void loadVectors(FILE *fFile);
void eraseVectors();
void addVector(char *sName, size_t iSize, int64_t *iCell);
void saveVectors();