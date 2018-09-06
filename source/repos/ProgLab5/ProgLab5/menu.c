#include "main.h"

menu_t createMenu(char *sTitle)
{
	menu_t mTemp;
	mTemp.iItemsCount = 0;
	mTemp.sTitle = sTitle;
	mTemp.miItems = NULL;

	return mTemp;
}

void addMenuItem(menu_t *mMenu, char *sText, char cItem, void *fnLink)
{
	menuitem_t miTemp = { sText, cItem, fnLink };

	mMenu->iItemsCount++;
	mMenu->miItems = (menuitem_t*)realloc(mMenu->miItems, mMenu->iItemsCount * sizeof(menuitem_t));
	mMenu->miItems[mMenu->iItemsCount - 1] = miTemp;
}

void menuShow(menu_t mMenu)
{
	system("cls");
	//printCurrentLoadedFile();
	printf("%s:\n", mMenu.sTitle);

	for (size_t i = 0; i < mMenu.iItemsCount; i++)
	{
		char cButton = (mMenu.miItems[i]).cItem;
		printf("%c. %s\n", toupper(cButton), (mMenu.miItems[i]).sText);
	}

	size_t iItem = UINT_MAX;

	while (1)
	{
		char cItem = _getch();

		for (size_t i = 0; i < mMenu.iItemsCount; i++)
		{
			if ((mMenu.miItems[i]).cItem == cItem)
			{
				iItem = i;
				break;
			}
		}

		if (iItem != UINT_MAX)
			break;

		continue;
	}

	(mMenu.miItems[iItem]).fnLink();
}

void menu()
{
	menu_t menuMain = createMenu("Main menu");

	addMenuItem(&menuMain, "File",			'1', l_fileMenu);
	addMenuItem(&menuMain, "Edit",			'2', l_editMenu);
	addMenuItem(&menuMain, "Operations",	'3', l_operationsMenu);
	addMenuItem(&menuMain, "Search\n",		'4', l_searchMenu);
	addMenuItem(&menuMain, "Exit",			'q', l_exitMenu);

	while (1)
	{
		menuShow(menuMain);
	}
}

void l_operationsMenu()
{
	menu_t menuOperations = createMenu("Operations");

	addMenuItem(&menuOperations, "Get value from index",	'1', l_operGetValue);
	addMenuItem(&menuOperations, "Sum vectors",				'2', l_operSum);
	addMenuItem(&menuOperations, "Substract vectors",		'3', l_operSubstract);
	addMenuItem(&menuOperations, "Multiply vector",			'4', l_operMultiply);
	addMenuItem(&menuOperations, "Divide vector\n",			'5', l_operDivide);

	addMenuItem(&menuOperations, "Back",					'b', doNothing);

	menuShow(menuOperations);
}

void l_operGetValue()
{
	system("cls");
	printf("Enter name of vector (leave this field empty to exit): ");

	char sTempName[MAX_VECTOR_NAME * 16];
	gets(sTempName);

	if (!strlen(sTempName))
	{
		l_operationsMenu();
		return;
	}

	if (strlen(sTempName) >= MAX_VECTOR_NAME)
	{
		printf("Vector name is too long... \nMax name length is %d", MAX_VECTOR_NAME - 1);
		_getch();

		l_operationsMenu();
		return;
	}

	char sName[MAX_VECTOR_NAME * 4 + 1];
	mysql_escape_string(sName, sTempName, (unsigned long)strlen(sTempName));

	char sQueryCheck[2048];
	sprintf(sQueryCheck, "SELECT size, data FROM vectors WHERE name = '%s' LIMIT 1;",
		sName);

	MYSQL *db = getDatabase();

	if (mysql_query(db, sQueryCheck))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_operationsMenu();
		return;
	}

	MYSQL_RES *res = mysql_store_result(db);
	MYSQL_ROW row = mysql_fetch_row(res);

	if (row == NULL)
	{
		printf("Error: there's no vector with name '%s'...",
			sName);
		_getch();

		mysql_free_result(res);

		l_operGetValue();
		return;
	}

	printf("\nVector:\t%s\nSize:\t%s\nValues:",
		sName, row[0]);

	char* sValue = strtok(row[1], ";");

	if (sValue == NULL)
	{
		printf("\nError: empty input in row: %s %s",
			row[0], row[1]);

		_getch();
		mysql_free_result(res);

		l_operationsMenu();
		return;
	}

	size_t iSize = atoi(row[0]);
	int64_t iCell[MAX_VECTOR_SIZE] = { 0 };

	for (size_t i = 0; i < iSize; i++)
	{
		iCell[i] = atoi(sValue);

		if (iSize > MAX_SHOW_ALL_SIZE)
		{
			if (i == MAX_SHOW_BOUNDS)
				printf("\n\t...   [%d..%zu]\n\n", MAX_SHOW_BOUNDS, iSize - MAX_SHOW_BOUNDS - 1);

			if (i >= MAX_SHOW_BOUNDS && i < iSize - MAX_SHOW_BOUNDS)
				continue;
		}

		printf("\t%s   [%zu]\n", sValue, i);
		sValue = strtok(NULL, ";");
	}

	size_t iValue = 0;
	putchar('\n');

	while (1)
	{
		printf("Enter index of cell [empty -> exit]: ");

		cleanLine();

		char sInput[128];
		gets(sInput);

		if (!strlen(sInput))
		{
			l_operationsMenu();

			mysql_free_result(res);
			return;
		}

		iValue = (size_t)atoi(sInput);

		if (!isInteger(sInput) || iValue < 0 || iValue > iSize)
		{
			putchar('\b');
			putchar('\r');

			continue;
		}

		cleanLine();
		break;
	}

	putchar('\b');
	putchar('\r');

	cleanLine();

	printf("Result: %s[%zu] = %I64d", sName, iValue, iCell[iValue]);

	mysql_free_result(res);
	_getch();
}

void l_operSum()
{
	system("cls");
	printf("Sum vectors: C = A + B\n");
	
	char sNames[2][MAX_VECTOR_NAME * 4 + 1];

	MYSQL *db = getDatabase();
	vector_t vTemp = { 1, { 0 }, "C" };

	for (int i = 0; i < 2; i++)
	{
		printf("\nEnter name of vector %c [empty->exit]: ", i ? 'B' : 'A');

		char sTempName[MAX_VECTOR_NAME * 2];
		gets(sTempName);

		if (!strlen(sTempName))
		{
			return;
		}

		if (strlen(sTempName) >= MAX_VECTOR_NAME)
		{
			printf("Vector name is too long... \nMax name length is %d", MAX_VECTOR_NAME - 1);
			_getch();

			return;
		}

		mysql_escape_string(sNames[i], sTempName, (unsigned long)strlen(sTempName));

		char sQuery[MAX_VECTOR_NAME * 8 + 256];
		sprintf(sQuery, "SELECT size, data FROM vectors WHERE name = '%s';", sNames[i]);

		if (mysql_query(db, sQuery))
		{
			printf("Failed to send query: Error: %s\n",
				mysql_error(db));

			_getch();
			return;
		}

		MYSQL_RES *res = mysql_store_result(db);
		MYSQL_ROW row = mysql_fetch_row(res);

		if (row == NULL)
		{
			printf("Error!!! Vector `%s` not found!!!", sNames[i]);
			_getch();

			mysql_free_result(res);
			return;
		}

		vTemp.iSize = max(vTemp.iSize, (size_t)atoi(row[0]));

		char* sValue = strtok(row[1], ";");

		if (sValue == NULL)
		{
			printf("\nError: empty input in row: %s %s",
				row[0], row[1]);

			_getch();
			return;
		}

		size_t iTempSize = (size_t)atoi(row[0]);

		printf("\nVector:\t%s\nSize:\t%zu\nValues:", sNames[i], iTempSize);

		for (size_t j = 0; j < iTempSize; j++)
		{
			int64_t iValue = (int64_t)atoi(sValue);
			printf("\t%I64d   [%zu]\n", iValue, j);

			vTemp.iCell[j] += iValue;
			sValue = strtok(NULL, ";");
		}

		mysql_free_result(res);
	}

	printf("\nResult.\n\nVector:\tC\nSize:\t%zu\nValues:", vTemp.iSize);

	for (size_t j = 0; j < vTemp.iSize; j++)
	{
		printf("\t%I64d   [%zu]\n", vTemp.iCell[j], j);
	}

	_getch();
}

void l_operSubstract()
{
	system("cls");
	printf("Substract vectors: C = A - B\n");

	char sNames[2][MAX_VECTOR_NAME * 4 + 1];

	MYSQL *db = getDatabase();
	vector_t vTemp = { 1, { 0 }, "C" };

	for (int i = 0; i < 2; i++)
	{
		printf("\nEnter name of vector %c [empty->exit]: ", i ? 'B' : 'A');

		char sTempName[MAX_VECTOR_NAME * 2];
		gets(sTempName);

		if (!strlen(sTempName))
		{
			return;
		}

		if (strlen(sTempName) >= MAX_VECTOR_NAME)
		{
			printf("Vector name is too long... \nMax name length is %d", MAX_VECTOR_NAME - 1);
			_getch();

			return;
		}

		mysql_escape_string(sNames[i], sTempName, (unsigned long)strlen(sTempName));

		char sQuery[MAX_VECTOR_NAME * 8 + 256];
		sprintf(sQuery, "SELECT size, data FROM vectors WHERE name = '%s';", sNames[i]);

		if (mysql_query(db, sQuery))
		{
			printf("Failed to send query: Error: %s\n",
				mysql_error(db));

			_getch();
			return;
		}

		MYSQL_RES *res = mysql_store_result(db);
		MYSQL_ROW row = mysql_fetch_row(res);

		if (row == NULL)
		{
			printf("Error!!! Vector `%s` not found!!!", sNames[i]);
			_getch();

			mysql_free_result(res);
			return;
		}

		vTemp.iSize = max(vTemp.iSize, (size_t)atoi(row[0]));

		char* sValue = strtok(row[1], ";");

		if (sValue == NULL)
		{
			printf("\nError: empty input in row: %s %s",
				row[0], row[1]);

			_getch();
			mysql_free_result(res);

			return;
		}

		size_t iTempSize = (size_t)atoi(row[0]);

		printf("\nVector:\t%s\nSize:\t%zu\nValues:", sNames[i], iTempSize);

		for (size_t j = 0; j < iTempSize; j++)
		{
			int64_t iValue = (int64_t)atoi(sValue);
			printf("\t%I64d   [%zu]\n", iValue, j);

			vTemp.iCell[j] += (i ? -1 : 1) * iValue;
			sValue = strtok(NULL, ";");
		}

		mysql_free_result(res);
	}

	printf("\nResult.\n\nVector:\tC\nSize:\t%zu\nValues:", vTemp.iSize);

	for (size_t j = 0; j < vTemp.iSize; j++)
	{
		printf("\t%I64d   [%zu]\n", vTemp.iCell[j], j);
	}

	_getch();
}

void l_operMultiply()
{
	l_operScalar(0);
}

void l_operDivide()
{
	l_operScalar(1);
}

void l_operScalar(int iMode)
{
	char sModeNames[2][16] = { "Multiply" , "Divide" };

	system("cls");
	printf("%s vector...\nEnter name of vector (leave this field empty to exit): ", sModeNames[iMode]);

	char sTempName[MAX_VECTOR_NAME * 16];
	gets(sTempName);

	if (!strlen(sTempName))
	{
		l_operationsMenu();
		return;
	}

	if (strlen(sTempName) >= MAX_VECTOR_NAME)
	{
		printf("Vector name is too long... \nMax name length is %d", MAX_VECTOR_NAME - 1);
		_getch();

		l_operationsMenu();
		return;
	}

	char sName[MAX_VECTOR_NAME * 4 + 1];
	mysql_escape_string(sName, sTempName, (unsigned long)strlen(sTempName));

	char sQueryCheck[2048];
	sprintf(sQueryCheck, "SELECT size, data FROM vectors WHERE name = '%s' LIMIT 1;",
		sName);

	MYSQL *db = getDatabase();

	if (mysql_query(db, sQueryCheck))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_operationsMenu();
		return;
	}

	MYSQL_RES *res = mysql_store_result(db);
	MYSQL_ROW row = mysql_fetch_row(res);

	if (row == NULL)
	{
		printf("Error: there's no vector with name '%s'...",
			sName);
		_getch();

		mysql_free_result(res);

		l_operGetValue();
		return;
	}

	printf("\nVector:\t%s\nSize:\t%s\nValues:",
		sName, row[0]);

	char* sValue = strtok(row[1], ";");

	if (sValue == NULL)
	{
		printf("\nError: empty input in row: %s %s",
			row[0], row[1]);

		_getch();
		mysql_free_result(res);

		l_operationsMenu();
		return;
	}

	size_t iSize = atoi(row[0]);
	int64_t iCell[MAX_VECTOR_SIZE] = { 0 };

	for (size_t i = 0; i < iSize; i++)
	{
		iCell[i] = atoi(sValue);

		printf("\t%s   [%zu]\n", sValue, i);
		sValue = strtok(NULL, ";");
	}

	printf("\nEnter scalar value (max +-999) [empty -> exit]: ");

	char sInput[128];
	gets(sInput);

	if (!strlen(sInput))
	{
		l_operationsMenu();
		return;
	}

	int iScalar = atoi(sInput);

	if (!isInteger(sInput) || strlen(sInput) > 3 || (iMode && !iScalar))
	{
		printf("Error! Incorrect value!");

		_getch();
		l_operationsMenu(0);
		return;
	}

	printf("\nVector:\t%s\nSize:\t%s\nValues:",
		sName, row[0]);

	for (size_t i = 0; i < iSize; i++)
	{
		if (!iMode)
		{
			iCell[i] *= iScalar;
		}
		else
		{
			iCell[i] /= iScalar;
		}

		printf("\t%I64d   [%zu]\n", iCell[i], i);
	}

	_getch();
	l_operationsMenu();
}

void l_fileMenu()
{
	menu_t menuFile = createMenu("File");

	addMenuItem(&menuFile, "Open",		'1', l_fileMenu_open);
	addMenuItem(&menuFile, "Save\n",	'2', l_fileMenu_save);
	addMenuItem(&menuFile, "Back",		'b', doNothing);

	menuShow(menuFile);
}

void l_fileMenu_open()
{
	system("cls");
	printf("Please enter the path to the file. \n  Leave this field empty to exit.\n  Write `def` to use default path for file.\n\n> ");

	char sInput[2048];
	gets(sInput);

	if (strcmp(sInput, "def") == 0)
	{
		strcpy(sInput, "C:\\Users\\Jake\\lab5out.vct");
	}

	if (!strlen(sInput))
	{
		l_fileMenu();
		return;
	}

	int bSuccess = tryToOpenFile(sInput);

	if (bSuccess)
	{
		printf("\n\nSuccessfully loaded file '%s'.\nPress any key to continue...\n", sInput);
		_getch();

		l_fileMenu();
		return;
	}

	system("cls");
	printf("Cannot load file '%s'.\nPlease try again.\n\nPress any key to continue...\n", sInput);
	_getch();

	l_fileMenu_open();
}

void l_fileMenu_save()
{
	saveVectors();
	_getch();
}

void l_addRandomItems()
{
	clock_t time = clock();
	MYSQL *db = getDatabase();

	if (mysql_query(db, "START TRANSACTION;"))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		return;
	}

	char sQuery[MAX_VECTOR_SIZE * 32 + 1024];
	system("cls");

	for (int i = 0; i < DEBUG_VECTORS_AMOUNT; i++)
	{
#if 1
		if (i % (DEBUG_VECTORS_AMOUNT / DEBUG_PRECISION) == 0)
		{
			printf("\rLoading: ");
		
			for (int j = 0; j < DEBUG_PRECISION; j++)
			{
				printf("%c", j < (i / (DEBUG_VECTORS_AMOUNT / DEBUG_PRECISION)) ? -78 : -80);
			}

			printf("\r");
		}
#else
		if (i % DEBUG_PRECISION == 0)
		{
			printf("\rL: %d", i);
		}
#endif
		int iSize = rand() % MAX_VECTOR_SIZE + 1;

		sprintf(sQuery, "INSERT INTO `vectors` (`name`, `size`, `data`) VALUES ('v%d', '%d', CONCAT(",
			i, iSize);

		for (int j = 1; j <= iSize; j++)
		{
			strcat(sQuery, RAND);
			strcat(sQuery, (j == iSize ? "));" : ", ';', "));
		}

		//puts(sQuery);
		//_getch();
		
		if (mysql_query(db, sQuery))
		{
			printf("\nFailed to send query: Error: %s\n",
				mysql_error(db));

			_getch();
			return;
		}
	}

	if (mysql_query(db, "COMMIT;"))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		return;
	}

	system("cls");
	printf("Loading time: %.5f sec.",
		(float)(clock() - time) / CLOCKS_PER_SEC);

	_getch();
}

void l_truncate()
{
	MYSQL *db = getDatabase();

	if (mysql_query(db, "TRUNCATE TABLE `vectors`"))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		return;
	}
}

void l_addItem()
{
	system("cls");
	printf("Adding vector.\nEnter name of vector (leave this field empty to exit): ");

	char sTempName[MAX_VECTOR_NAME * 2];
	gets(sTempName);

	if (!strlen(sTempName))
	{
		l_editMenu();
		return;
	}

	if (strlen(sTempName) >= MAX_VECTOR_NAME)
	{
		printf("Vector name is too long... \nMax name length is %d", MAX_VECTOR_NAME - 1);
		_getch();

		l_editMenu();
		return;
	}

	char sName[MAX_VECTOR_NAME * 4 + 1];
	mysql_escape_string(sName, sTempName, (unsigned long)strlen(sTempName));

	char sQueryCheck[2048];
	sprintf(sQueryCheck, "SELECT size FROM vectors WHERE name = '%s' LIMIT 1;",
		sName);

	MYSQL *db = getDatabase();

	if (mysql_query(db, sQueryCheck))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		l_editMenu();

		return;
	}

	MYSQL_RES *res = mysql_store_result(db);
	MYSQL_ROW row = NULL;

	if (mysql_fetch_row(res) != NULL)
	{
		printf("Error: there's existing vector with name '%s'...",
			sName);
		_getch();

		mysql_free_result(res);
		l_editMenu();

		return;
	}

	mysql_free_result(res);

	printf("Enter vector size: ");

	char sValue[2048];
	gets(sValue);

	if (!isInteger(sValue))
	{
		printf("Error: '%s' is not integer value...",
			sValue);
		_getch();

		l_editMenu();
		return;
	}

	int iSize = atoi(sValue);

	if (iSize < 1 || iSize > MAX_VECTOR_SIZE)
	{
		printf("Error: '%s' is not correct vector size value... Max size is %zu",
			sValue, MAX_VECTOR_SIZE);
		_getch();

		l_editMenu();
		return;
	}

	char sBuffer[32768];
	strcpy(sBuffer, "");

	for (int i = 1; i <= iSize; i++)
	{
		printf("Enter dimension %d [enter -> 0]: ", i);
		gets(sValue);

		if (!isInteger(sValue))
		{
			printf("\b\r");
			cleanLine();
			i--;

			continue;
		}

		sprintf(sValue, "%d", atoi(sValue));

		strcat(sBuffer, sValue);
		strcat(sBuffer, (i == iSize) ? "" : ";");
	}

	char sQuery[32768];

	sprintf(sQuery, "INSERT INTO vectors (`name`, `size`, `data`) VALUES ('%s', '%d', '%s');",
		sName, iSize, sBuffer);

	//puts(sQuery);
	//_getch();

	if (mysql_query(db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_editMenu();
		return;
	}

	printf("\nSuccesfully saved vector `%s`...",
		sName);
	_getch();

	l_editMenu();
}

void l_deleteItem()
{
	system("cls");
	printf("Deleting vector.\nEnter name of vector (leave this field empty to exit): ");

	char sTempName[MAX_VECTOR_NAME * 2];
	gets(sTempName);

	if (!strlen(sTempName))
	{
		l_editMenu();
		return;
	}

	if (strlen(sTempName) >= MAX_VECTOR_NAME)
	{
		printf("Vector name is too long... \nMax name length is %d", MAX_VECTOR_NAME - 1);
		_getch();

		l_editMenu();
		return;
	}

	char sName[MAX_VECTOR_NAME * 4 + 1];
	mysql_escape_string(sName, sTempName, (unsigned long)strlen(sTempName));

	char sQuery[MAX_VECTOR_NAME * 4 + 256];
	sprintf(sQuery, "DELETE FROM vectors WHERE name = '%s';", sName);

	MYSQL *db = getDatabase();

	if (mysql_query(db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		l_editMenu();
		return;
	}

	printf("Successfully deleted vector '%s'", sName);
	_getch();

	l_editMenu();
}

void l_editMenu()
{
	menu_t menuEdit = createMenu("Edit");

	addMenuItem(&menuEdit, "Add an item to table",			'1', l_addItem);
	addMenuItem(&menuEdit, "Delete an item from table\n",	'2', l_deleteItem);

#ifdef DEBUG
	addMenuItem(&menuEdit, "Add random items to DB *",		'a', l_addRandomItems);
	addMenuItem(&menuEdit, "Truncate table *\n",			's', l_truncate);
#endif

	addMenuItem(&menuEdit, "Back", 'b', doNothing);

	menuShow(menuEdit);
}

void drawTable(MYSQL_RES *res, MYSQL_ROW row, int iMaxLenName, int iMaxLenData)
{
	iMaxLenData = min(123, iMaxLenData);

#if 1
	printf("\n…");

	for (int i = 0; i < iMaxLenName + 2; i++)
		printf("Õ");

	printf("À");

	for (int i = 0; i < 6; i++)
		printf("Õ");

	printf("À");

	for (int i = 0; i < iMaxLenData + 2; i++)
		printf("Õ");

	printf("ª\n");
#endif
#if 1
	printf("∫ %-*s ∫ %-4s ∫ %-*s ∫\n", iMaxLenName, "name", "size", iMaxLenData, "data");

	printf("Ã");

	for (int i = 0; i < iMaxLenName + 2; i++)
		printf("Õ");

	printf("Œ");

	for (int i = 0; i < 6; i++)
		printf("Õ");

	printf("Œ");

	for (int i = 0; i < iMaxLenData + 2; i++)
		printf("Õ");

	printf("π\n");

#endif
	while ((row = mysql_fetch_row(res)))
	{
		size_t iLen = strlen(row[2]);

		if (iLen > iMaxLenData)
		{
			row[2][iMaxLenData - 1]	= '.';
			row[2][iMaxLenData - 2] = '.';
			row[2][iMaxLenData - 3] = '.';
			row[2][iMaxLenData]		= '\0';
		}

		printf("∫ %-*s ∫ %-4s ∫ %-*s ∫\n", iMaxLenName, row[0], row[1], iMaxLenData, row[2]);
	}

	printf("»");

	for (int i = 0; i < iMaxLenName + 2; i++)
		printf("Õ");

	printf(" ");

	for (int i = 0; i < 6; i++)
		printf("Õ");

	printf(" ");

	for (int i = 0; i < iMaxLenData + 2; i++)
		printf("Õ");

	printf("º\n");
}

void l_listItems()
{
	system("cls");

	char sQuery[MAX_VECTOR_NAME * 4 + 256];
	MYSQL *db = getDatabase();

	sprintf(sQuery, "SELECT max(length(name)), max(length(data)) FROM vectors ORDER BY name ASC LIMIT 50;");

	if (mysql_query(db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_searchMenu();
		return;
	}

	MYSQL_RES *res = mysql_store_result(db);
	MYSQL_ROW row = mysql_fetch_row(res);

	int iMaxLenName = 4;
	int iMaxLenData = 4;

	if (row[0] != NULL)
	{
		iMaxLenName = max(iMaxLenName, atoi(row[0]));
		iMaxLenData = max(iMaxLenData, atoi(row[1]));

		//printf("%s %s\n\n", row[0], row[1]);
	}

	mysql_free_result(res);

	sprintf(sQuery, "SELECT name, size, data FROM vectors ORDER BY name ASC LIMIT 50;");

	if (mysql_query(db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_searchMenu();
		return;
	}

	res = mysql_store_result(db);
	row = NULL;

	drawTable(res, row, iMaxLenName, iMaxLenData);
	mysql_free_result(res);

	_getch();
	l_searchMenu();
}

void l_searchByName()
{
	system("cls");
	printf("Search vector by name.\nEnter part of name of vector: ");

	char sTempName[MAX_VECTOR_NAME * 2];
	gets(sTempName);

	if (strlen(sTempName) >= MAX_VECTOR_NAME)
	{
		printf("Vector name is too long... \nMax name length is %d", MAX_VECTOR_NAME - 1);
		_getch();

		l_searchMenu();
		return;
	}

	char sName[MAX_VECTOR_NAME * 4 + 1];
	mysql_escape_string(sName, sTempName, (unsigned long)strlen(sTempName));

	char sQuery[MAX_VECTOR_NAME * 4 + 256];
	MYSQL *db = getDatabase();

	sprintf(sQuery, "SELECT max(length(name)), max(length(data)) FROM vectors WHERE name LIKE '%%%s%%' ORDER BY name ASC LIMIT 20;", sName);

	if (mysql_query(db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_searchMenu();
		return;
	}

	MYSQL_RES *res = mysql_store_result(db);
	MYSQL_ROW row = mysql_fetch_row(res);

	int iMaxLenName = 4;
	int iMaxLenData = 4;

	if (row[0] != NULL)
	{
		iMaxLenName = max(iMaxLenName, atoi(row[0]));
		iMaxLenData = max(iMaxLenData, atoi(row[1]));

		//printf("%s %s\n\n", row[0], row[1]);
	}

	mysql_free_result(res);

	sprintf(sQuery, "SELECT name, size, data FROM vectors WHERE name LIKE '%%%s%%' ORDER BY name ASC LIMIT 20;", sName);

	if (mysql_query(db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_searchMenu();
		return;
	}

	res = mysql_store_result(db);
	row = NULL;

	drawTable(res, row, iMaxLenName, iMaxLenData);

	mysql_free_result(res);
	_getch();

	l_searchMenu();
}

void l_searchBySize()
{
	system("cls");
	printf("Search vector by size (leave this field empty to exit): ");

	char sInput[MAX_VECTOR_NAME * 2];
	gets(sInput);

	if (!isInteger(sInput) || !strlen(sInput))
	{
		l_searchMenu();
		return;
	}

	int iValue = atoi(sInput);

	char sQuery[MAX_VECTOR_NAME * 4 + 256];
	MYSQL *db = getDatabase();

	sprintf(sQuery, "SELECT max(length(name)), max(length(data)) FROM vectors WHERE size = '%d' ORDER BY name ASC LIMIT 20;", iValue);

	if (mysql_query(db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_searchMenu();
		return;
	}

	MYSQL_RES *res = mysql_store_result(db);
	MYSQL_ROW row = mysql_fetch_row(res);

	int iMaxLenName = 4;
	int iMaxLenData = 4;

	if (row[0] != NULL)
	{
		iMaxLenName = max(iMaxLenName, atoi(row[0]));
		iMaxLenData = max(iMaxLenData, atoi(row[1]));

		//printf("%s %s\n\n", row[0], row[1]);
	}

	mysql_free_result(res);

	sprintf(sQuery, "SELECT name, size, data FROM vectors WHERE size = '%d' ORDER BY name ASC LIMIT 20;", iValue);

	if (mysql_query(db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();

		l_searchMenu();
		return;
	}

	res = mysql_store_result(db);
	row = NULL;

	drawTable(res, row, iMaxLenName, iMaxLenData);

	mysql_free_result(res);
	_getch();

	l_searchMenu();
}

void l_searchMenu()
{
	menu_t menuSearch = createMenu("Search");

	addMenuItem(&menuSearch, "List 50 first items sorted by name",	'1', l_listItems);
	addMenuItem(&menuSearch, "Search by name",						'2', l_searchByName);
	addMenuItem(&menuSearch, "Search by size\n",					'3', l_searchBySize);

	addMenuItem(&menuSearch, "Back",								'b', doNothing);

	menuShow(menuSearch);
}

void l_exitMenu()
{
	exit(1);
}

void doNothing()
{

}