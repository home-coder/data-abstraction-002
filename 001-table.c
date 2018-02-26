/*************************************************************************
 > Filename   : 001-table.c
 > Author     : oneface - one_face@sina.com
 > Company    : 江山如画
 > Time       : 2018-02-24 18:51:01
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _table_data {
	int *data;					/* table real data */
	unsigned int lenght;		/* data real size */
	unsigned int size;			/* malloc size */
}table_data;

static void table_show(table_data *tdata)
{
	int i;
	table_data *tdata_p = tdata;
	if (!tdata_p) {
		printf("tdata is not exsit\n");
		return ;
	}

	for (i = 0; i < tdata_p->lenght; i++) {
		printf("%d->", tdata_p->data[i]);
	}
	printf("\n");
}

static void table_init(table_data **tdata, unsigned int size)
{
	if (*tdata != NULL) {
		return ;
	}

	*tdata = (table_data *)malloc(sizeof(table_data));
	if (!*tdata) {
		printf("tdata malloc failed\n");
		return ;
	}

	(*tdata)->data = (int *)malloc(sizeof(int) * size);
	if (!(*tdata)->data) {
		printf("(*tdata)->data malloc failed\n");	
		return ;
	}
	memset((*tdata)->data, 0x0, size);
	(*tdata)->size = size;

	(*tdata)->lenght = 0;
}

static void table_insert(table_data *tdata, unsigned int loc, int data)
{
	int i;
	table_data *tdata_p = tdata;

	if (!tdata_p) {
		printf("tdata is not exsit\n");
		return ;
	}

	if (loc < 0 || loc > tdata_p->lenght + 1) {
		//invalid
		printf("insert loc %u is invalid\n", loc);
		return ;
	}

	if (tdata_p->lenght == tdata_p->size) {
		//realloc
		printf("memory is low, realloc\n");
		tdata_p->data = (int *)realloc(tdata_p->data, 8 * sizeof(int));
		if (!tdata_p->data) {
			printf("tdata_p->data realloc failed\n");
			return ;
		}
	}

	for (i = tdata_p->lenght; i > loc; i--) {
		tdata_p->data[i] = tdata_p->data[i-1];
	}

	tdata_p->data[loc] = data;
	tdata_p->lenght++;
}

int main()
{
	table_data *tdata;
	table_show(tdata);

	table_init(&tdata, 10);
	printf("tdata size is %d\n", tdata->size);

	table_insert(tdata, 0, 9);
	table_insert(tdata, 0, 8);
	table_insert(tdata, 1, 3);
	table_insert(tdata, 0, 1);
	table_insert(tdata, 4, 2);
	table_show(tdata);

#if 0
	table_amend(tdata, 1, 7);

	table_delet(tdata, 5);
	table_delet(tdata, 0);

	unsigned int loc = table_select(tdata, 7);
	printf("loc is %d\n", loc);

#endif
	table_show(tdata);
exit:
	free(tdata);
	return 0;
}
