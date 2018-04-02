/*************************************************************************
 > Filename   : 002-slink.c
 > Author     : oneface - one_face@sina.com
 > Company    : 江山如画
 > Time       : 2018-02-26 13:45:45
 ************************************************************************/

// 头节点  首元节点
/* head -> first -> ... -> NULL*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _slink_data {
	char data;
	struct _slink_data *next;
}slink_data;

static void slink_show(slink_data *sldata)
{
	if (!sldata) {
		printf("sldata is not exsit\n");
		return ;
	}

	while (sldata->next) {
		sldata = sldata->next;
		printf("%c->", sldata->data);
	}
	printf("\n");
}

static void slink_init(slink_data **sldata)
{
	if (*sldata != NULL) {
		printf("sldata is already exsit\n");
		return ;
	}

	*sldata = (slink_data *)malloc(sizeof(slink_data));
	if (!*sldata) {
		printf("sldata malloc failed\n");
		return ;
	}

	(*sldata)->next = NULL;
}

static void slink_insert(slink_data *sldata, unsigned int loc, char data)
{
	slink_data *p_sldata = NULL;
	slink_data *n_sldata = NULL;
	int i = 0;

	p_sldata = sldata;

	if (!p_sldata) {
		printf("sldata is not exsit\n");
		return ;
	}

	for (i = 0; i < loc; i++) {
		p_sldata = p_sldata->next;
		if (!p_sldata) {
			printf("loc %u is invalid\n", loc);
			return ;
		}
	}
#if 0 //不是栈空间，所以以下逻辑不适用
	if (loc < 0 || loc > p_sldata->length + 1) {
		printf("insert loc %u is invalid\n", loc);
		return ;
	}
#endif

	n_sldata = (slink_data *)malloc(sizeof(slink_data));
	if (!n_sldata) {
		printf("n_sldata malloc failed\n");
		return ;
	}
#if 0 //不是栈空间，所以以下逻辑不适用
	n_sldata->data = data;
	p_sldata = p_sldata + loc;
	n_sldata->next = p_sldata->next;
	p_sldata->next = n_sldata;
	p_sldata->length++;
#endif
	n_sldata->data = data;
	n_sldata->next = p_sldata->next;
	p_sldata->next = n_sldata;
}

static void slink_delet(slink_data *sldata, unsigned int loc)
{
	slink_data *p_sldata = sldata, *d_sldata;
	unsigned int i;

	if (!p_sldata) {
		printf("sldata is not exsit\n");
		return ;
	}

	for (i = 0; i < loc; i++) {
		p_sldata = p_sldata->next;
		if (!p_sldata) {
			printf("loc %u is invalid\n", loc);
			return ;
		}
	}
	d_sldata = p_sldata->next;
	p_sldata->next = p_sldata->next->next;
	free(d_sldata);
	d_sldata = NULL;
}

static void slink_amend(slink_data *sldata, unsigned int loc, char data)
{
	slink_data *p_sldata = sldata;
	unsigned int i;

	if (!p_sldata) {
		printf("sldata is not exsit\n");
		return ;
	}

	for (i = 0; i < loc; i++) {
		p_sldata = p_sldata->next;
		if (!p_sldata || !p_sldata->next) {
			printf("loc %u is invalid\n", loc);
			return ;
		}
	}
	p_sldata->next->data = data;
}

static unsigned int slink_select(slink_data *sldata, char data)
{
	slink_data *p_sldata = sldata;
	unsigned int i = 0;

	if (!p_sldata) {
		printf("sldata is not exsit\n");
		return ;
	}

	while (p_sldata->next) {
		p_sldata = p_sldata->next;
		if (p_sldata->data == data) {
			return i;	
		}
		i++;
	}
	return -1;
}

int main()
{
	slink_data *ldata = NULL;

	slink_show(ldata);
	slink_init(&ldata);
	slink_show(ldata);
	slink_insert(ldata, 0, 'a');
	slink_show(ldata);
	slink_insert(ldata, 0, '9');
	slink_show(ldata);
	slink_insert(ldata, 1, 'm');
	slink_show(ldata);
	slink_insert(ldata, 0, 'e');
	slink_insert(ldata, 4, 'm');
	slink_show(ldata);
	slink_insert(ldata, 7, 'n');
	slink_show(ldata);

	slink_delet(ldata, 4);
	slink_show(ldata);

	slink_delet(ldata, 0);
	slink_show(ldata);
	slink_delet(ldata, 5);
	slink_show(ldata);


	slink_amend(ldata, 3, 'u');
	slink_amend(ldata, 4, 'm');
	slink_amend(ldata, 0, 'y');
	slink_show(ldata);

	int loc;
	loc = slink_select(ldata, 'u');
	printf("select data 'u' is in loc %d\n", loc);
	loc = slink_select(ldata, 'y');
	printf("select data 'y' is in loc %d\n", loc);
	loc = slink_select(ldata, 'm');
	printf("select data 't' is in loc %d\n", loc);

	return 0;
}
