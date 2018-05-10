/***************************************************************************
 > Filename   : 006-huffman.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-09 13:36:55
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char hftype;

typedef struct {
	hftype value;
	int weight;
	int parent, rchild, lchild;
}hftree;

typedef char* hfcode;

static void hfman_select(hftree *ht, int end, int *s1, int *s2)
{
	int i = 1;
	int tmp;

	while (ht[i].parent != -1 && i <= end) {
		i++;
	}
	*s1 = i;

	i++;
	while (ht[i].parent != -1 && i <= end) {
		i++;
	}
	*s2 = i;

	if (ht[*s1].weight > ht[*s2].weight) {
		tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
	}

	for (++i; i <= end; i++) {
		if (ht[i].parent == -1) {
			if (ht[i].weight < ht[*s1].weight) {
				*s2 = *s1;
				*s1 = i;
			} else if (ht[i].weight >= ht[*s1].weight && ht[i].weight < ht[*s2].weight) {
				*s2 = i;
			}
		}
	}
}

static void hfman_creat(hftree **ht, int *w, int s)
{
	int i;
	int m = 2 * s - 1;

	*ht = (hftree *)malloc((m + 1) * sizeof(hftree));
	if (NULL == *ht) {
		printf("ht malloc failed\n");
		return ;
	}
	hftree *p = *ht;

	for (i = 1; i <= s; i++) {
		(p + i)->weight = w[i - 1];
		(p + i)->parent = -1;
		(p + i)->rchild = -1;
		(p + i)->lchild = -1;
	}

	for (i = s + 1; i <= m; i++) {
		(p + i)->weight = -1;
		(p + i)->parent = -1;
		(p + i)->rchild = -1;
		(p + i)->lchild = -1;
	}

	int s1, s2;
	for (i = s + 1; i <= m; i++) {
		hfman_select(p, i - 1, &s1, &s2);
		printf("s1:%d, s2:%d\n", s1, s2);
		p[s1].parent = p[s2].parent = i;
		p[i].lchild = s1;
		p[i].rchild = s2;
		p[i].weight = p[s1].weight + p[s2].weight;
	}
}

static void hfman_code(hftree *ht, hfcode **hc, int s)
{
	int i, j, start;
	char *code = (char *)malloc((s - 1) * sizeof(char));

	memset(code, '\0', s - 1);
	*hc = (hfcode *)malloc(s * sizeof(hfcode));

	for (i = 1; i <= s; i++) {
		int c = i;
		start = s - 1;
		while (ht[c].parent != -1) {
			j = ht[c].parent;
			if (ht[j].lchild == c) {
				code[--start] = '0';
			} else if (ht[j].rchild == c) {
				code[--start] = '1';
			}
			c = j;
		}
		(*hc)[i] = (hfcode )malloc((s-start) * sizeof(char));
		printf("%s\n", &code[start]);
		strncpy((*hc)[i], &code[start], s-start);
	}

	free(code);
}

static void hfcode_print(hfcode *hc, int *w, int s)
{
	int i;
	for (i = 0; i < s; i++) {
		printf("%d: %s\n", w[i], hc[i+1]);
	}

}

static void hftnode_setval(hftree *ht, int *w, int s)
{
	int i;
	for (i = 1; i < s; i++) {
		(ht + i)->value = w[i-1];
	}
}

int main()
{
	hftree *ht = NULL;

	int w[] = {2, 8, 7, 6, 5, 4};
	int s = sizeof(w) / sizeof(w[0]);

	hfman_creat(&ht, w, s);

	hfcode *hc = NULL;	
	hfman_code(ht, &hc, s);

	hfcode_print(hc, w, s);

	hftnode_setval(ht, w, s);

	return 0;
}
