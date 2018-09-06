// lab4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <io.h>

int check(char c) {
	if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y') {
		return 1;
	}
	else {
		return 0;
	}
}

int main(int argc, char *argv[])
{	
	system("cls");
	//printf("Press any key to begin\n");
	//_getch();
	int i = 0, size; 
	//char words[10000];
	if (argc == 1) {
		printf("Please provide the name of file.\n");
		return 1;
	} 
	else {
		FILE *f = fopen(argv[1], "r");
		if (f != NULL) {
			fseek(f, 0, SEEK_END);
			size = ftell(f);
			fseek(f, 0, SEEK_SET);
			//printf("%ld\n", size);
			char *words = (char *)malloc(size * sizeof(char));
			do {
				fscanf(f, "%s", words);
				if (check(words[0])) {
					words[0] = tolower(words[0]);
				}
				printf("%s ", words);
			} while (!feof(f));
			printf("\n");
			free(words);
			fclose(f);
			return 0;
		}
		else {
			printf("File '%s' not found.\n", argv[1]);
			return 2;
		}
	}
	//printf("Bye! Press any key to exit!");
	//_getch();
}