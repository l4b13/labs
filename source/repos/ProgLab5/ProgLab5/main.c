#include "main.h"
//#define CLOCK

MYSQL db;

int main()
{
#ifdef CLOCK
	clock_t sum = 0;
	size_t amount = 0;

	int i = 500;

	while (1)
	{
		clock_t time = clock();

		/* Enter code here...	*/

		printf("\rLoading: ");

		for (int j = 0; j < DEBUG_PRECISION; j++)
		{
			putchar(j < (i / (DEBUG_VECTORS_AMOUNT / DEBUG_PRECISION)) ? '²' : '°');
		}

		/* Stop					*/		

		time = clock() - time;
		amount++;

		sum += time;

		printf("\n\nN: %u A: %f\n",
			time, (float)sum / amount);

		_getch();
	}
#endif

	mysql_init(&db);
	mysql_options(&db, MYSQL_READ_DEFAULT_GROUP, "lab_five");

	if (!mysql_real_connect(&db, CFG_SERVER, CFG_USER, CFG_PASS, CFG_DATABASE, 0, NULL, 0))
	{
		printf("Failed to connect to database: Error: %s\n",
			mysql_error(&db));

		return -1;
	}

	mysql_set_character_set(&db, "utf8");

	if (mysql_query(&db, "CREATE TABLE IF NOT EXISTS `vectors` ( \
							`name` VARCHAR(128) PRIMARY KEY, \
							`size` INTEGER default '1', \
							`data` TEXT );"))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(&db));
		return -2;
	}

#ifdef DEBUG
#if INSERT_DATA_WAY == INSERT_SEND_A_LOT_QUERIES
	char sQuery[32768];

	/* Not optimized */
	for (int i = 0; i < 100; i++)
	{
		sprintf(sQuery, "INSERT INTO `vectors` (`name`, `size`, `data`) VALUES ('%d_victor', '%d', '%d;%d;%d')", i, 3, rand(), rand(), rand());

		if (mysql_query(&db, sQuery))
		{
			printf("Failed to send query: Error: %s\n",
				mysql_error(&db));
			return i - 100;
		}
	}
#elif INSERT_DATA_WAY == INSERT_SEND_ONE_QUERY
	char sQuery[32768];

	/* Optimized! */
	sprintf(sQuery, "INSERT INTO `vectors` (`name`, `size`, `data`) VALUES");

	for (int i = 0; i < 100; i++)
	{
		sprintf(sQuery, "%s ('vec_%d', '%d', '%d;%d;%d')%s",
			sQuery, i, 3, -i, i, i * i, (i == 99 ? ";" : ","));
	}

	if (mysql_query(&db, sQuery))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(&db));
		return -3;
	}
#endif

	if (mysql_query(&db, "SELECT `name`, `size`, `data` FROM `vectors` LIMIT 10;"))
	{
		printf("Failed to send query: Error: %s\n",
			mysql_error(&db));
		return -2;
	}

	MYSQL_RES *res = mysql_store_result(&db);
	MYSQL_ROW row = NULL;

	while ((row = mysql_fetch_row(res)))
	{
		printf("ó %-9s ó %s ó %17s ó\n", row[0], row[1], row[2]);
	}

	mysql_free_result(res);
	//_getch();
#endif

	menu();
	return 0;
}

MYSQL* getDatabase()
{
	return &db;
}

int isDouble(char *sText)
{
	size_t k = 0, len = strlen(sText);

	for (size_t i = 0; i < len; i++)
	{
		if (sText[i] == '.')
			k++;
		else if (!(sText[i] >= '0' && sText[i] <= '9' || sText[i] == '.' || sText[i] == '-') || k > 1 || (sText[i] == '-' && i > 0))
			return 0;
	}

	return 1;
}

int isInteger(char *sText)
{
	size_t len = strlen(sText), t = 0;

	for (size_t i = 0; i < len; i++)
	{
		if (!(sText[i] >= '0' && sText[i] <= '9' || sText[i] == '-' || sText[i] == '\n') || (sText[i] == '-' && i > 0))
			return 0;
	}

	return 1;
}

int copy_file(char *sOldFile, char  *sNewFile)
{
	FILE  *ptr_old, *ptr_new;
	errno_t err = 0, err1 = 0;
	int  a;

	err = fopen_s(&ptr_old, sOldFile, "rb");
	err1 = fopen_s(&ptr_new, sNewFile, "wb");

	if (err != 0)
		return  -1;

	if (err1 != 0)
	{
		fclose(ptr_old);
		return  -1;
	}

	while (1)
	{
		a = fgetc(ptr_old);

		if (!feof(ptr_old))
			fputc(a, ptr_new);
		else
			break;
	}

	fclose(ptr_new);
	fclose(ptr_old);
	return  0;
}

void cleanLine()
{
	for (int i = 0; i < 256; i++)
		putchar(' ');

	for (int i = 0; i < 256; i++)
		putchar('\b');
}
