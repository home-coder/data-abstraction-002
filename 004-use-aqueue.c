/***************************************************************************
 > Filename   : 004-use-aqueue.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-21 10:15:57
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX 32

typedef struct {
	char elem[MAX];
	int front, rear;
	unsigned int lenght;
}aqueue;

static const char *hc[] = {
	"011001111100",
	"11000111",
	"001",
	"110110110110101",
	"0101",
	"00111100",
};

static void init_aqueue(aqueue **aque)
{
	*aque = (aqueue *)malloc(sizeof(**aque));
	if (*aque) {
		(*aque)->front = (*aque)->rear = 0;
		(*aque)->lenght = 0;
	}
}

static void en_aqueue(aqueue *aque, char elem)
{
	if (aque->rear && aque->rear % MAX == aque->front) {
		printf("queue full\n");
		return ;
	}
	aque->elem[aque->rear++] = elem;	
	aque->lenght++;
}

static void de_aqueue(aqueue *aque, char *elem)
{
	if (aque->front && aque->front % MAX == aque->rear) {
		printf("queue null\n");
		return ;
	}
	*elem = aque->elem[aque->front++];
	aque->lenght--;
}

int main(int argc, char **argv)
{
	int i, j;
	char bits, bit;

	if (argc < 2) {
		fprintf(stderr, "argc invalid\n");
		return -1;
	}

	aqueue *aque = NULL;
	init_aqueue(&aque);

	for (i = 1; i < argc; i++) {
		const char *map = hc[argv[i][0] - 'a'];
		//入队列
		printf("map: %s\n", map);
		while (*map) {
			en_aqueue(aque, *map);
			map++;
			if (aque->lenght > 8) {
				j = 8;
				while (j--) {
					de_aqueue(aque, &bit);
					printf("bit:%c\n", bit);
					bits = bits | ((bit - '0') << j);
				}
				printf("bits = %c\n", bits);
			}
		}
	}

	return 0;
}
