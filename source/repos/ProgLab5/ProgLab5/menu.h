#pragma once

#include "vector.h"

typedef struct
{
	char *sText;
	char cItem;
	void(*fnLink)();
} menuitem_t;

typedef struct
{
	size_t iItemsCount;
	menuitem_t *miItems;
	char *sTitle;
} menu_t;

void menu();

void l_fileMenu();
void l_fileMenu_open();
void l_fileMenu_save();

void l_editMenu();
void l_searchMenu();
void l_exitMenu();

void doNothing();
void l_truncate();

void l_operationsMenu();
void l_operGetValue();
void l_operSum();
void l_operSubstract();
void l_operMultiply();
void l_operDivide();
void l_operScalar(int iMode);