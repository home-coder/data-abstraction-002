/***************************************************************************
  > Filename   : huffman514.c
  > Author     : oneface - one_face@sina.com
  > Company    : 一尊还酹江月
  > Time       : 2018-05-14 09:35:40
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
	int parent, rchild, lchild;
}hftree;

typedef char* hfcode;

static void creat_huffman(hftree **hft, int *w, int s)
{
	int m = 2 * s - 1;
	int i, j, s1, s2, tmp;

	*hft = (hftree *)malloc((m + 1) * sizeof(hftree));
	if (!*hft) {
		printf("hftree malloc failed\n");
		return ;
	}

	for (i = 1; i <= s; i++) {
		(*hft)[i].weight = w[i - 1];
		(*hft)[i].parent = -1;
		(*hft)[i].rchild = -1;
		(*hft)[i].lchild = -1;
	}

	for (; i <= m; i++) {
		(*hft)[i].weight = -1;
		(*hft)[i].parent = -1;
		(*hft)[i].rchild = -1;
		(*hft)[i].lchild = -1;
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
		//set huffman
		printf("j=%d, s1: %d, s2:%d\n", j, s1, s2);
		(*hft)[j].weight = (*hft)[s1].weight + (*hft)[s2].weight;
		(*hft)[s1].parent = (*hft)[s2].parent = j;
		(*hft)[j].lchild = s1;
		(*hft)[j].rchild = s2;
	}
}

static void huffman_code(hfcode **hcd, hftree *hft, int s)
{
	int i, j, start;

	char *code = (char *)malloc(s * sizeof(char));
	if (!code) {
		printf("code malloc failed\n");
		goto fail1;
	}
	code[s - 1] = '\0';

	*hcd = (hfcode *)malloc(s * sizeof(hfcode));
	if (!*hcd) {
		printf("*hcd malloc failed\n");
		goto fail2;
	}

	for (i = 1; i <= s; i++) {
		int c = i;
		start = s - 1;// '\0'
		while (hft[c].parent != -1) {
			j = hft[c].parent;
			printf("le le ha %d, j = %d\n", start, j); 
			if (hft[j].lchild == c) {
				code[--start] = '0';	
			} else if (hft[j].rchild == c) {
				code[--start] = '1';
			}
			c = j;
		}

		(*hcd)[i] = (hfcode)malloc((s - start + 1) * sizeof(***hcd));
		//memcpy((void *)(*hcd)[i], (const void *)&code[start], s - start);
		strncpy((void *)(*hcd)[i], (const void *)&code[start], s - start + 1);
	}

fail2:
	free(code);
fail1:
	return ;
}

static void print_hfcode(hfcode *hcd, int *w, int s)
{
	int i;
	for (i = 1; i <= s; i++) {
		printf("%d: %s\n", w[i - 1], hcd[i]);	
	}
}

int main()
{
	hftree *hft = NULL;
	int w[] = {2, 8, 7, 6, 5, 4};
	int s = sizeof(w) / sizeof(w[0]);

	creat_huffman(&hft, w, s);

	hfcode *hcd = NULL;
	huffman_code(&hcd, hft, s);
	print_hfcode(hcd, w, s);

	return 0;
}
