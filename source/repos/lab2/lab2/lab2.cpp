// lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

double min(double a, double b) {
	if (a < b) {
		return a;
	}
	else return b;
}

double funkciya(double fxstart, double fradius) {
	if (fxstart <= -fradius) {
		return fxstart + fradius;
	}
	if (fxstart > -fradius && fxstart < 0) {
		return sqrt(fradius*fradius - fxstart*fxstart);
	}
	if (fxstart >= 0 && fxstart < 6) {
		return fradius * (6 - fxstart) / 6;
	}
	if (fxstart >= 6) {
		return fxstart - 6;
	}
}

int main()
{	
	double radius, xstart, xend, deltax, y, xlast, xcurrent;
	//double rad, xs, xe, de;
	char symbol;
	int radstatus, xstartstatus, xendstatus, deltaxstatus;
	const char luBor = 201, ldBor = 200, Hor = 205, Ver = 186, Cen = 206, ruBor = 187, rdBor = 188, forsenOMEGA = 203, forsenSleeper = 202, forsenE = 204, forsenGASM = 185;
	do {
		printf("Input radius value: ");
		if (scanf("%lf", &radius) != 1 || radius <= 0) {
			rewind(stdin);
			printf("Wrong input parameter, radius must contain numbers and be more than 0. Press 'y' for repeat, or any other for exit from application... ");
			symbol = getche();
			printf("\n");
			if (symbol != 'y') {
				exit(0);
			}
		}
		else {
			radstatus = 1;
			break;
		}
	} while (1);
	do {
		printf("Input Xstart: ");
		if (scanf("%lf", &xstart) != 1) {
			rewind(stdin);
			printf("Wrong input parameter, Xstart must contain numbers. Press 'y' for repeat, or any other for exit from application... ");
			symbol = getche();
			printf("\n");
			if (symbol != 'y') {
				exit(0);
			}
		}
		else {
			xstartstatus = 1;
			break;
		}
	} while (1);

	do {
		printf("Input Xend: ");
		if (scanf("%lf", &xend) != 1 || xend<=xstart) {
			rewind(stdin);
			printf("Wrong input parameter, Xend must contain numbers and be more than Xstart. Press 'y' for repeat, or any other for exit from application... ");
			symbol = getche();
			printf("\n");
			if (symbol != 'y') {
				exit(0);
			}
		}
		else {
			xendstatus = 1;
			break;
		}
	} while (1);

	if (xendstatus == 1) {
		do {
			printf("Input delta X: ");
			if (scanf("%lf", &deltax) != 1 || deltax>xend-xstart || deltax<=0) {
				rewind(stdin);
				printf("Wrong input parameter, deltaX must contain numbers, be more than 0 and be less than (Xstart-Xend). Press 'y' for repeat, or any other for exit from application... ");
				symbol = getche();
				printf("\n");
				if (symbol != 'y') {
					exit(0);
				}
			}
			else {
				deltaxstatus = 1;
				break;
			}
		} while (1);
	}
	if (radstatus + xstartstatus + xendstatus + deltaxstatus == 4) {
		xlast = floor((xstart-1) * 1000) / 1000;
		xcurrent = floor(xstart * 1000) / 1000;
		printf("%c", luBor);
		for (int i = 0; i < 24; i++) {
			printf("%c", Hor);
		}
		printf("%c", forsenOMEGA);
		for (int i = 0; i < 24; i++) {
			printf("%c", Hor);
		}
		printf("%c\n", ruBor);
		printf("%c            X           %c            Y           %c\n", Ver, Ver, Ver);
		printf("%c", forsenE);
		for (int i = 0; i < 24; i++) {
			printf("%c", Hor);
		}
		printf("%c", Cen);
		for (int i = 0; i < 24; i++) {
			printf("%c", Hor);
		}
		printf("%c\n", forsenGASM);
		//printf("┌────────────────────────┬────────────────────────┐\n");
		//printf("│            X           │            Y           │\n");
		//printf("├────────────────────────┼────────────────────────┤\n");
		while (xstart < xend) {
			y = funkciya(xstart, radius);
			if (xcurrent != xlast) {
				printf("%c%24.3lf%c%24.3lf%c\n", Ver, xstart, Ver, y, Ver);
			}
			xlast = xcurrent;
			xstart += deltax;
			xcurrent = floor(xstart * 1000) / 1000;
			if (xstart >= xend && xcurrent != xlast) {
				printf("%c%24.3lf%c%24.3lf%c\n", Ver, min(xstart, xend), Ver, funkciya(min(xstart, xend), radius), Ver);
			}
		}
		printf("%c", ldBor);
		for (int i = 0; i < 24; i++) {
			printf("%c", Hor);
		}
		printf("%c", forsenSleeper);
		for (int i = 0; i < 24; i++) {
			printf("%c", Hor);
		}
		printf("%c\n", rdBor);
		//printf("└────────────────────────┴────────────────────────┘");
	}
	printf("Press any key to exit... ");
	getch();
    return 0;
}