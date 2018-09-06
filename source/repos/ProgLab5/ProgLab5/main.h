#pragma once

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4133)
#pragma warning(disable : 4013)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <mysql.h>
#include <time.h>

#define INSERT_DISABLED				0
#define INSERT_SEND_A_LOT_QUERIES	1
#define INSERT_SEND_ONE_QUERY		2

#define RAND						"FLOOR((RAND() - 0.5)*10000000)"

//#define DEBUG
#define INSERT_DATA_WAY				INSERT_DISABLED

#define DEBUG_VECTORS_AMOUNT		5000
#define DEBUG_PRECISION				50

#define MAX_LINE_LEN				2048
#define N							1

#define MAX_SHOW_BOUNDS				2
#define MAX_SHOW_ALL_SIZE			(2 * MAX_SHOW_BOUNDS + 2)

#define CFG_SERVER					"localhost"
#define CFG_USER					"labs"
#define CFG_DATABASE				"lab5"
#define CFG_PASS					"hMLptTsEgFU"

#include "menu.h"
#include "file.h"
#include "vector.h"

int isDouble(char *sText);
int isInteger(char *sText);
int copy_file(char *sOldFile, char  *sNewFile);

void cleanLine();

MYSQL* getDatabase();