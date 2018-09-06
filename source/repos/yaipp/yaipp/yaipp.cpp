// yaipp.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	if (argc == 1) {
		printf("Please provide the name of file.\n");
		return 1;
	}
	else {
		FILE *f = fopen(argv[1], "rb");
		if (f != NULL) {
			fseek(f, 0, SEEK_END);
			long arr_size = ftell(f);
			char *bin_string = new char[arr_size];
			fseek(f, 0, SEEK_SET);
			fscanf(f, "%s", bin_string);
			for (long i = 0; i < arr_size; i++) {
				printf("%3d", bin_string[i]);
				if ((i + 1) % 16 == 0) {
					printf("\n");
				}
			}
			fclose(f);
			printf("\n");
			printf("Completed!");
			_getch;
			return 0;
		}
		else {
			printf("File '%s' not found.\n", argv[1]);
			return 2;
		}
	}
    return 0;
}

