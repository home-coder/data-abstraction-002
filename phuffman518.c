/***************************************************************************
 > Filename   : phuffman518.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-18 09:16:13
 > Description: 刘涵羽

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _hftree {
	int weight;
	struct _hftree *parent, *lchild, *rchild;
}hftree;

typedef char* hfcode;

static void huffman_creat(hftree **hft, int *w, int s)
{
	int i, j, tmp, s1, s2;
	int m = 2 * s - 1;

	*hft = (hftree *)malloc((m + 1) * sizeof(**hft));
	if (!*hft) {
		printf("*hft malloc failed\n");
		return ;
	}

	for (i = 1; i <= s; i++) {
		(*hft)[i].weight = w[i - 1];
		(*hft)[i].parent = (*hft)[i].lchild = (*hft)[i].rchild;
	}
	for (; i <= m; i++) {
		(*hft)[i].weight = -1;
		(*hft)[i].parent = (*hft)[i].lchild = (*hft)[i].rchild;
	}

	for (j = s + 1; j <= m; j++) {
		i = 1;
		while ((*hft)[i].parent != NULL && i <= j - 1) {
			i++;
		}
		s1 = i;

		++i;
		while ((*hft)[i].parent != NULL && i <= j - 1) {
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
			if ((*hft)[i].parent == NULL) {
				if ((*hft)[i].weight < (*hft)[s1].weight) {
					s2 = s1;
					s1 = i;
				} else if ((*hft)[i].weight > (*hft)[s1].weight && (*hft)[i].weight < (*hft)[s2].weight) {
					s2 = i;
				}
			}
		}

		printf("s1=%d, s2=%d\n", s1, s2);
		(*hft)[j].weight = (*hft)[s1].weight + (*hft)[s2].weight;
		(*hft)[j].lchild = &(*hft)[s1];
		(*hft)[j].rchild = &(*hft)[s2];
		(*hft)[s1].parent = (*hft)[s2].parent = &(*hft)[j];
	}
}

static void huffman_code(hfcode **hfc, hftree *hft, int s)
{
	int i;

	*hfc = (hfcode *)malloc(s * sizeof(**hfc));
	if (!*hfc) {
		printf("*hfc malloc failed\n");
		return ;
	}

	char *code = (char *)malloc(s * sizeof(char));
	if (!code) {
		printf("code malloc failed\n");
		return ;
	}
	code[s - 1] = '\0';

	for (i = 1; i <= s; i++) {
		int start = s - 1;
		while (hft[i].parent != NULL) {
			//FIXME 采用指针下面的实现就显得很Low
			if (hft[i].parent->lchild && hft[i].parent->lchild->weight == hft[i].weight) {
				code[--start] = '0';
			} else if (hft[i].parent->rchild && hft[i].parent->rchild->weight == hft[i].weight) {
				code[--start] = '1';
			} else {
				printf("hehe\n");
			}

			hft[i] = *hft[i].parent;
		}
		(*hfc)[i] = (hfcode )malloc((s - start + 1) * sizeof(***hfc));
		strncpy((*hfc)[i], &code[start], s - start + 1);
	}
}

static void hfcode_print(hfcode *hfc, int *w, int s)
{
	int i;
	for (i = 1; i <= s; i++) {
		printf("%d: %s\n", w[i - 1], hfc[i]);
	}
}

int main()
{
	int w[] = {2, 8, 7, 6, 5, 4};
	int s = sizeof(w) / sizeof(w[0]);

	hftree *hft = NULL;
	huffman_creat(&hft, w, s);

	hfcode *hfc = NULL;
	huffman_code(&hfc, hft, s);

	hfcode_print(hfc, w, s);

	return 0;
}
