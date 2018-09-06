// lab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "my_queue.h"

int main()
{
	//rebuild 1.0
	const int size = 1000;
	long int i, qel;
	char qcommand[size];
	printf("Obudov Vladislav 13 BAPUAHT.\n");
	printf("Please choose part of task (1/2): ");
	char id = _getche();
	printf("\n");
	switch (id) {
		case '1': {
			queue ochered;
			printf("Part 1 - Queue.\n");
			printf("Available commands: 1.enqueue {number} 2.dequeue 3.done.\n");
			while (1) {
				scanf("%s", &qcommand);
				for (i = 0; i < strlen(qcommand); i++) {
					qcommand[i] = tolower(qcommand[i]);
				}
				if (strcmp(qcommand, "enqueue") == 0) {
					scanf("%ld", &qel);
					ochered.enqueue(qel);
					ochered.show();
				}
				else if (strcmp(qcommand, "dequeue") == 0) {
					if (ochered.dequeue() == 0) {
						ochered.show();
					}
				}
				else if (strcmp(qcommand, "done") == 0) {
					break;
				}
				else {
					printf("Incorrect command, please try again!\n");
				}
				rewind(stdin);
			}
			ochered.theend();
			break;
		}
		case '2': {
			long int width, height, neww = 0, newh = 0, rstat, j;
			printf("Part 2 - Matrix.\n");
			printf("Input matrix size.\n");
			do {
				printf("Input width: ");
				rstat = scanf("%ld", &width);
				if (rstat == 0) {
					printf("Wrong input parameter! Please try again!");
				}
			} while (rstat == 0);
			do {
				printf("Input height: ");
				rstat = scanf("%ld", &height);
				if (rstat == 0) {
					printf("Wrong input parameter! Please try again!");
				}
			} while (rstat == 0);
			long int ** matrix = (long int **)malloc(size * sizeof(long int *));
			for (int i = 0; i < size; i++) {
				matrix[i] = (long int *)malloc(sizeof(long int)*size);
			}
			printf("Input matrix elements:\n");
			for (i = 0; i < height; i++) {
				do {
					rstat = 0;
					for (j = 0; j < width; j++) {
						rstat = rstat + scanf("%ld", &matrix[i][j]);
					}
					if (rstat != width) {
						rewind(stdin);
						printf("Wrong input parameters! Please write a raw again!\n");
					}
				} while (rstat != width);
			}
			while (1) {
				printf("Available commands: 1.roll-down {x} 2.roll-right {x} 3.done.\n");
				scanf("%s", &qcommand);
				for (i = 0; i < strlen(qcommand); i++) {
					qcommand[i] = tolower(qcommand[i]);
				}
				if (strcmp(qcommand, "roll-right") == 0) {
					if (scanf("%ld", &qel) != 1) {
						printf("Wrong input parameters! Please write a raw again!\n");
					}
					else {
						qel = qel % width;
						for (i = neww; i < neww + qel; i++) {
							for (j = newh; j < newh + height; j++) {
								matrix[j][i + width] = matrix[j][i];
							}
						}
						neww = neww + qel;
						for (i = newh; i < newh + height; i++) {
							for (j = neww; j < neww + width; j++) {
								printf("%ld ", matrix[i][j]);
							}
							printf("\n");
						}
					}
				}
				else if (strcmp(qcommand, "roll-down") == 0) {
					if (scanf("%ld", &qel) != 1) {
						printf("Invalid operation! Wrong parameter number, please try again.\n");
					}
					else {
						qel = qel % height;
						for (i = newh; i < newh + qel; i++) {
							for (j = neww; j < neww + width; j++) {
								matrix[i + height][j] = matrix[i][j];
							}
						}
						newh = newh + qel;
						for (i = newh; i < newh + height; i++) {
							for (j = neww; j < neww + width; j++) {
								printf("%ld ", matrix[i][j]);
							}
							printf("\n");
						}
					}
				}
				else if (strcmp(qcommand, "done") == 0) {
					break;
				}
				else {
					printf("Incorrect command, please try again!\n");
				}
				rewind(stdin);
			}
			for (i = 0; i < size; i++) {
				free(matrix[i]);
			}
			free(matrix);
			break;
		}
		default: {
			printf("Invalid part number, type '1' or '2'\n");
			break;
		}
	}
	printf("Bye! Press any key to exit.");
	_getche();
    return 0;
}