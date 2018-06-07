/***************************************************************************
 > Filename   : hufman525.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-25 19:08:34
 > Description: 明天再搞

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct _hfmtree{
	int weight;
	struct _hfmtree *parent, *lchild, *rchild;
}hfmtree;

typedef uint8_t location;
typedef char* hfmcode;

static void hfmtree_creat(hfmtree **phfmt, int *w, int s)
{
	location l, r, i, j, tmp;

	int nz = 2 * s - 1;
	*phfmt = (hfmtree *)malloc((nz + 1) * sizeof(**phfmt));
	if (!*phfmt) {
		printf("*phfmt malloc failed\n");
		return ;
	}

	for (i = 1; i <= s; i++) {
		(*phfmt)[i].weight = w[i - 1];
		(*phfmt)[i].parent = (*phfmt)[i].lchild = (*phfmt)[i].rchild = NULL;
	}
	for (; i <= nz; i++) {
		(*phfmt)[i].weight = -1;
		(*phfmt)[i].parent = (*phfmt)[i].lchild = (*phfmt)[i].rchild = NULL;
	}

	for (i = s + 1; i <= nz; i++) {
		j = 1;
		while ((*phfmt)[j].parent && j < i) {
			j++;
		}
		l = j;

		++j;
		while ((*phfmt)[j].parent && j < i) {
			j++;	
		}
		r = j;

		if ((*phfmt)[l].weight > (*phfmt)[r].weight) {
			tmp = l;
			l = r;
			r = tmp;
		}

		++j;
		for (; j < i; j++) {
			if (!(*phfmt)[j].parent) {
				if ((*phfmt)[j].weight < (*phfmt)[l].weight) {
					r = l;
					l = j;
				} else if ((*phfmt)[j].weight > (*phfmt)[l].weight && (*phfmt)[j].weight < (*phfmt)[r].weight) {
					r = j;
				}
			}
		}
		printf("debug: l=%d, r=%d\n", l, r);
		(*phfmt)[i].weight = (*phfmt)[l].weight + (*phfmt)[r].weight;
		(*phfmt)[l].parent = (*phfmt)[r].parent = &(*phfmt)[i];
		(*phfmt)[i].lchild = &(*phfmt)[l];
		(*phfmt)[i].rchild = &(*phfmt)[r];
	}
}

static void hfmcode_creat(hfmcode **phfmc, hfmtree *hfmt, int s)
{
	int i, start;
	hfmtree *phfmt = NULL;

	*phfmc = (hfmcode *)malloc(s * sizeof(**phfmc));
	if (!*phfmc) {
		printf("*phfmc malloc failed\n");
		return ;
	}

	hfmcode code = (hfmcode )malloc(s * sizeof(*code));
	if (!code) {
		printf("code malloc failed\n");
		return ;
	}
	code[s - 1] = '\0';

	for (i = 1; i <= s; i++) {
		start = s - 1;
		phfmt = &hfmt[i];
		while (phfmt->parent) {
			if (phfmt->parent->lchild == phfmt) {
				code[--start] = '0';
			} else if (phfmt->parent->rchild == phfmt) {
				code[--start] = '1';
			}
			phfmt = phfmt->parent;;
		}
		(*phfmc)[i] = (hfmcode )malloc((s - start + 1) * sizeof(***phfmc));
		strncpy((*phfmc)[i], &code[start], s - start + 1);
	}
}

static void hfmcode_print(hfmcode *hfmcode, int *w, int s)
{
	int i;
	for (i = 1; i <= s; i++) {
		printf("%d: %s\n", w[i - 1], hfmcode[i]);
	}
}

int main()
{
	char *elem = "hecdjuhecdjuecdjuecdjuecdjecdejej";
	int w[] = {2, 8, 7, 6, 5, 4};
	int s = sizeof(w) / sizeof(w[0]);

	hfmtree *hfmt = NULL;
	hfmtree_creat(&hfmt, w, s);

	hfmcode *hfmc = NULL;
	hfmcode_creat(&hfmc, hfmt, s);
	hfmcode_print(hfmc, w, s);

	return 0;
}
