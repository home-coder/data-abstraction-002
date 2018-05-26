/***************************************************************************
 > Filename   : 024.c
 > Author     : oneface - one_face@sina.com
 > Company    : 一尊还酹江月
 > Time       : 2018-05-17 18:36:35
 > Description: 

 - This program is free software; you can redistribute it and/or modify it
 - under the terms of the GNU General Public License as published by the
 - Free Software Foundation;  either version 2 of the  License, or (at your
 - option) any later version.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

static void char_to_bits(char *argv, char **pbitbuf)
{
	int i, j;
	char src = argv[0];

	*pbitbuf = (char *)malloc(9 * sizeof(char));
	for (i = 7, j = 0; i >= 0; i--) {
		(*pbitbuf)[j++] = '0' + ((src & (1 << i)) >> i);
	}
	(*pbitbuf)[8] = '\0';

	printf("pbitbuf: %s\n", *pbitbuf);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "argc invalid\n");
		return -1;
	}

	char *bitbuf = NULL;
	char_to_bits(argv[1], &bitbuf);
	printf("pbitbuf: %s\n", bitbuf);

	return 0;
}

