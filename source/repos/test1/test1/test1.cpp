// test1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>


int main()
{
	int a;
	scanf("%i",&a);
	if (scanf("%i", &a) != 1) {
		printf("error");
	}
	else {
		printf("success");
	}
    return 0;
}

