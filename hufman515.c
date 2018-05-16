/***************************************************************************
 > Filename   : hufman515.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-15 11:36:00
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int weight;
	int parent, lchild, rchild;
}hftree;

typedef char* hfcode;

static void huffman_creat(hftree **hft, int *w, int s)
{
	int m = 2 * s - 1;
	int i, j, tmp, s1, s2;

	if (!*hft) {
		*hft = (hftree *)malloc((m + 1) * sizeof(**hft));
		if (!*hft) {
			printf("*hft malloc failed\n");
			goto fail1;
		}
	}

	for (i = 1; i <= s; i++) {
		(*hft)[i].weight = w[i - 1];
		(*hft)[i].parent = -1;
		(*hft)[i].lchild = (*hft)[i].rchild = -1;
	}

	for (; i <= m; i++) {
		(*hft)[i].weight = -1;
		(*hft)[i].parent = -1;
		(*hft)[i].lchild = (*hft)[i].rchild = -1;
	}

	for (j = s + 1; j <= m; j++) {
		i = 1;
		while ((*hft)[i].parent != -1 && i <= j - 1) {
			i++;
		}
		s1 = i;

		++i;
		while ((*hft)[i].parent != -1 && i <= j - 1) {
			i++;	
		}
		s2 = i;

		if ((*hft)[s1].weight > (*hft)[s2].weight) {
			tmp = s1;
			s1 = s2;
			s2 = tmp;
		}

		++i;
		for (; i <= j - 1; i++) {
			if ((*hft)[i].parent == -1) {
				if ((*hft)[i].weight < (*hft)[s1].weight) {
					s2 = s1;
					s1 = i;
				} else if ((*hft)[i].weight > (*hft)[s1].weight && (*hft)[i].weight < (*hft)[s2].weight) {
					s2 = i;
				}
			}
		}

		printf("debug: j=%d, s1=%d, s2=%d\n", j, s1, s2);
		(*hft)[j].weight = (*hft)[s1].weight + (*hft)[s2].weight;
		(*hft)[j].lchild = s1;
		(*hft)[j].rchild = s2;
		(*hft)[s1].parent = (*hft)[s2].parent = j;
	}

fail1:
	return ;

}

static void huffman_code(hfcode **hfc, hftree *hft, int s)
{
	int i, j, start;

	if (!hft) {
		printf("hft is null, exit\n");
		return ;
	}

	if (!*hfc) {
		*hfc = (hfcode *)malloc(s * sizeof(**hfc));
		if (!*hfc) {
			printf("*hfc malloc failed\n");
			goto fail1;
		}
	}

	char *code = (char *)malloc(s * sizeof(char));
	if (!code) {
		printf("code malloc failed\n");
		goto fail2;
	}
	code[s - 1] = '\0';

	for (i = 1; i <= s; i++) {
		int c = i;
		start = s - 1;
		while (hft[c].parent != -1) {
			j = hft[c].parent;
			if (hft[j].lchild == c) {
				code[--start] = '0';	
			} else if (hft[j].rchild == c) {
				code[--start] = '1';
			}
			c = j;
		}

		(*hfc)[i] = (hfcode )malloc((s - start + 1) * sizeof(***hfc));
		if (!(*hfc)[i]) {
			printf("(*hfc)[i] malloc failed\n");
			goto fail3;
		}

		strncpy((*hfc)[i], &code[start], s - start + 1);
	}

fail3:
	free(code);
	return ;
fail2:
	free(*hfc);
fail1:
	return ;
}

static void huffman_code_print(hfcode *hfc, int *w, int s)
{
	int i;

	for (i = 1; i <= s; i++) {
		if (!hfc[i]) {
			printf("fuck null\n");
		}
		printf("%d: %s\n", w[i - 1], hfc[i]);
	}

}

int main()
{
	//creat huffman tree
	hftree *hft = NULL;
	int w[] = {2, 8, 7, 6, 5, 4};
	int s = sizeof(w) /sizeof(w[0]);
	huffman_creat(&hft, w, s);

	//code huffman
	hfcode *hfc = NULL;
	huffman_code(&hfc, hft, s);

	//print huffman code
	huffman_code_print(hfc, w, s);

	return 0;
}
