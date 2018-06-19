/***************************************************************************
 > Filename   : phuffman615.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-06-15 13:50:57
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct _hfmtree{
	int weight;
	struct _hfmtree *parent, *lchild, *rchild;
} hfmtree;

typedef char* hfmcode;

static void hft_creat(hfmtree **phft, int *w, int s)
{
	int i, j, tmp, s1, s2;
	int m = 2 * s - 1;

	*phft = (hfmtree *)malloc(sizeof(**phft) * (m + 1));
	if (!*phft) {
		printf("*phft malloc failed\n");
		return ;
	}

	for (i = 1; i <= s; i++) {
		(*phft)[i].weight = w[i - 1];
		(*phft)[i].lchild = (*phft)[i].rchild = (*phft)[i].parent = NULL;
	}
	for (; i <= m; i++) {
		(*phft)[i].weight = - 1;
		(*phft)[i].lchild = (*phft)[i].rchild = (*phft)[i].parent = NULL;
	}

	for (j = s + 1; j <= m; j++) {
		i = 1;
		while ((*phft)[i].parent != NULL && i < j) {
			i++;	
		}
		s1 = i;

		++i;
		while ((*phft)[i].parent != NULL && i < j) {
			i++;
		}
		s2 = i;

		if ((*phft)[s1].weight > (*phft)[s2].weight) {
			tmp = s1;
			s1 = s2;
			s2 = tmp;
		}

		++i;
		for (; i < j; i++) {
			if ((*phft)[i].parent == NULL) {
				if ((*phft)[s1].weight > (*phft)[i].weight) {
					s2 = s1;
					s1 = i;
				} else if ((*phft)[s1].weight < (*phft)[i].weight && (*phft)[i].weight < (*phft)[s2].weight) {
					s2 = i;
				}
			}
		}

		printf("s1=%d, s2=%d\n", s1, s2);
		(*phft)[i].weight = (*phft)[s1].weight + (*phft)[s2].weight;
		(*phft)[s1].parent = (*phft)[s2].parent = &(*phft)[i];
		(*phft)[i].lchild = &(*phft)[s1];
		(*phft)[i].rchild = &(*phft)[s2];
	}
}

static void hft_code(hfmcode **hfc, hfmtree *hft, int s)
{
	int i, j;
	hfmtree *phft = NULL;

	*hfc = (hfmcode *)malloc(sizeof(**hfc) * s);

	for (i = 1; i <= s; i++) {
		(*hfc)[i] = (hfmcode )malloc(sizeof(***hfc) * (s - 1));
		(*hfc)[i][s - 2] = '\0';
		j = s - 3;
		phft = &hft[i];
		while (phft->parent) {
			if (phft->parent->lchild == phft) {
				(*hfc)[i][j--] = '0';
			} else if (phft->parent->rchild == phft) {
				(*hfc)[i][j--] = '1';
			}
			phft = phft->parent;
		}
		(*hfc)[i] = (*hfc)[i] + j + 1;
	}
}

static void hftcode_print(hfmcode *hfc, int *w, int s)
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

	hfmtree *hft = NULL;
	hft_creat(&hft, w, s);

	hfmcode *hfc;
	hft_code(&hfc, hft, s);

	hftcode_print(hfc, w, s);

	return 0;
}
