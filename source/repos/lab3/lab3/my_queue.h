#pragma once

#include "stdafx.h"

struct queue {
	int size = 1000;
	long int * current = (long int *)malloc(size);
	int qstart = 0;
	int qend = 0;
	int enqueue(long int el);
	int dequeue();
	int show();
	int theend();
};

int queue::enqueue(long int el) {
	current[qend] = el;
	qend++;
	return 0;
}

int queue::dequeue() {
	if (qend - qstart > 0) {
		qstart++;
		return 0;
	}
	else {
		printf("Invalid operation!Queue is empty, please try again.\n");
		return 1;
	}
}

int queue::show() {
	if (qend - qstart != 0) {
		printf("Queue: ");
		for (int i = qstart; i < qend; i++) {
			printf("%ld ", current[i]);
		}
		printf("\n");
	}
	else {
		printf("Queue is empty\n");
	}
	return 0;
}

int queue::theend() {
	free(current);
	return 0;
}
