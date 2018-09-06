// lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
//#include <conio.h>

int main()
{
	long long id, brk;
	double a, b, func1, func2;
	char c;
	char alpha[] = "";
	char beta[] = "";
	brk = 0;
	//c[0] = '\0';
	//alpha[0] = '\0';
	//beta[0] = '\0';
	do {
		printf("1. Compute a function\n");
		printf("2. Exit\n");
		printf("Choose a menu item: ");
		scanf("%lli", &id);
		switch (id) {
		case 1: {
			printf("F1 = (sin(A)+cos(2B-A))/(cos(A)-sin(2B-A))\n");
			printf("F2 = (1+sin(2B))/cos(2B)\n");
			while (1 == 1) {
				printf("Input argument A: ");
				scanf("%s", alpha);
				if (strlen(alpha) < 20 && alpha[0] >= '0' && alpha[0] <= '9') {
					a = atof(alpha);
					brk = 0;
					break;
				}
				else {
					printf("Wrong input argument A. Print 'y' to continue, another key to return back: ");
					scanf("%c", &c);
					if (c != 'y') {
						brk = 1;
						break;
					}
				}
			}
			if (brk == 0) {
				while (1 == 1) {
					printf("Input argument B: ");
					scanf("%s", beta);
					if (strlen(beta) < 20 && beta[0] >= '0' && beta[0] <= '9') {
						b = atol(beta);
						break;
					}
					else {
						printf("Wrong input argument B. Print 'y' to continue, another key to return back: ");
						scanf("%c", &c);
						if (c != 'y') {
							brk = 1;
							break;
						}
					}
				}
			}
			if (brk == 0) {
				func1 = (sin(a) + cos(2 * b - a)) / (cos(a) - sin(2 * b - a));
				printf("F1 = %0.3lf\n", func1);
				func2 = (1 + sin(2 * b)) / cos(2 * b);
				printf("F2 = %0.3lf\n", func2);
				brk = 0;
			}
		}
			case 2: 
				exit(1);
			default: 
				printf("Please, choose a correct menu item!\n");
		}
	} while (1==1);
	return 0;
}