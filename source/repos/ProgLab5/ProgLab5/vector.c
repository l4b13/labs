#include "main.h"

int iVectorsAmount = 0;

void addVector(char *sName, size_t iSize, int64_t *iCell)
{
	
}

void eraseVectors()
{
	MYSQL *db = getDatabase();

	if (mysql_query(db, "TRUNCATE TABLE `vectors`;"))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		return;
	}
}

void loadVectors(FILE *fFile)
{
	clock_t time = clock();

	l_truncate();
	iVectorsAmount = 0;

	fseek(fFile, 0, SEEK_END);
	size_t iSize = ftell(fFile) / sizeof(vector_t);
	rewind(fFile);

	char sTemp[128];
	char sQuery[2048];

	MYSQL *db = getDatabase();

	if (mysql_query(db, "START TRANSACTION;"))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		return;
	}

	for (size_t i = 1; i <= iSize; i++)
	{
		vector_t vTemp;
		fread(&vTemp, sizeof(vector_t), 1, fFile);

		sprintf(sQuery, "INSERT INTO `vectors` (`name`, `size`, `data`) VALUES ('%s', '%zu', '%I64d", vTemp.sName, vTemp.iSize, vTemp.iCell[0]);

#ifdef DEBUG
		/*printf(" * %-8s %-3zu", vTemp.sName, vTemp.iSize);

		for (int i = 0; i < MAX_VECTOR_SIZE; i++)
			printf(" %-5I64d", vTemp.iCell[i]);

		printf("\n");*/
#endif
#if 1
		if (i % DEBUG_PRECISION == 0)
			printf("\rL: %zu", i);
#endif
		for (size_t j = 1; j < vTemp.iSize; j++)
		{
			sprintf(sTemp, ";%I64d", vTemp.iCell[j]);
			strcat(sQuery, sTemp);
		}
		
		strcat(sQuery, "');");

		if (mysql_query(db, sQuery))
		{
			printf("\nFailed to send query: Error: %s\n",
				mysql_error(db));

			_getch();

			return;
		}

		/*printf("%d/%zu vectors loaded.\n",
			iVectorsAmount, iSize);*/
	}

	if (mysql_query(db, "COMMIT;"))
	{
		printf("\nFailed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		return;
	}

	fclose(fFile);

	printf("\nLoaded %zu vectors...\nLoading time: %.5f sec.", 
		iSize, (float)(clock() - time) / CLOCKS_PER_SEC);
}

void saveVectors()
{
	clock_t time = clock();

	system("cls");
	printf("Saving vectors to %s\n", OUT_PATH);

	FILE *fFile = fopen(OUT_PATH, "wb");
	
	vector_t vTemp;
	MYSQL *db = getDatabase();

	if (mysql_query(db, "SELECT `name`, `size`, `data` FROM `vectors`;"))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(db));

		_getch();
		return;
	}

	printf("\rL: -");

	MYSQL_RES *res = mysql_store_result(db);
	MYSQL_ROW row = NULL;

	printf("\rL: --");

	int count = 0;
	
	while ((row = mysql_fetch_row(res)))
	{
		memset(vTemp.iCell, 0, MAX_VECTOR_SIZE * sizeof(int64_t));

		strcpy(vTemp.sName, row[0]);
		vTemp.iSize = atoi(row[1]);

		if (vTemp.iSize > MAX_VECTOR_SIZE || vTemp.iSize < 1)
		{
			printf("\nError: Vector `%s` size is %zu.. [Max is %zu]\n",
				row[0], vTemp.iSize, MAX_VECTOR_SIZE);
			continue;
		}

		//for (size_t i = 0; i < vTemp.iSize; i++)
		char* sValue = strtok(row[2], ";");

		if (sValue == NULL)
		{
			printf("\nError: empty input in row: %s %s %s",
				row[0], row[1], row[2]);
			continue;
		}

		size_t iCount = 0;

		do
		{
			vTemp.iCell[iCount] = atoi(sValue);
			iCount++;
		}
		while ((sValue = strtok(NULL, ";")) != NULL && iCount < vTemp.iSize);

		if (sValue != NULL && iCount == vTemp.iSize)
		{
			printf("\nWarning: Vector `%s` has size %s but values amount more than size: %s\n\n",
				row[0], row[1], row[2]);
			_getch();
		}

#ifdef DEBUG
		/*printf(" * %-8s %-3zu", vTemp.sName, vTemp.iSize);

		for (int i = 0; i < MAX_VECTOR_SIZE; i++)
			printf(" %-5I64d", vTemp.iCell[i]); 

		printf("\n");*/
#endif

		fwrite(&vTemp, sizeof(vector_t), 1, fFile);

#if 1
		if (++count % DEBUG_PRECISION == 0)
			printf("\rL: %d", count);
#endif
	}

	mysql_free_result(res);
	fclose(fFile);

	printf("\nSuccessful save...\nTime elapsed: %.5f sec.",
		(float)(clock() - time) / CLOCKS_PER_SEC);
	_getch();
}