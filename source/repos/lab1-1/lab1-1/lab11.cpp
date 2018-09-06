// lab11.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>

int main()
{
	do {
		char c;
		double a, b, f1, f2;
		int a1, b1, id, alpha = 0, beta = 0;
		printf("1. Compute a function\n");
		printf("2. Exit\n");
		printf("Choose a menu item: ");
		//scanf("%i", &id);
		id = getche();
		printf("\n");
		switch (id) {
		case '1': {
			printf("F1 = (sinA + cos(2B-A))/(cosA-sin(2B-A))\n");
			printf("F2 = (1 + sin2B)/cos2B\n");
			while (1) {
				printf("Input argument A: ");
				a1 = scanf("%lf", &a);
				rewind(stdin);
				if (a1) {
					break;
				}
				else {
					printf("Wrong input argument A. Print 'y' to continue, another key to return back: ");
					//scanf("%c", &c);
					c = getche();
					printf("\n");
					if (c != 'y') {
						alpha = 1;
						break;
					}
					else {
						continue;
					}
				}
				//fflush(stdin);
				//scanf("%*[^\n]");
				printf("%i", a1);
			}
			if (alpha == 0) {
				while (1) {
					printf("Input argument B: ");
					b1 = scanf("%lf", &b);
					rewind(stdin);
					if (b1) {
						break;
					}
					else {
						printf("Wrong input argument B. Print 'y' to continue, another key to return back: ");
						//scanf("%c", &c);
						c = getche();
						printf("\n");
						if (c != 'y') {
							beta = 1;
							break;
						}
						else {
							continue;
						}
					}
					//scanf("%*[^\n]");
				}
			}
			if (alpha + beta == 0) {
				f1 = (sin(a) + cos(2 * b - a)) / (cos(a) - sin(2 * b - a));
				f2 = (1 + sin(2 * b)) / cos(2 * b);
				printf("F1 = %0.3lf\n", f1);
				printf("F2 = %0.3lf\n", f2);
			}
			a = 0;
			b = 0;
			alpha = 0;
			beta = 0;
			break;
		}
		case '2':
			exit(1);
		default:
			printf("Please, choose a correct menu item!\n");
		}
	} while (1==1);
    return 0;
}