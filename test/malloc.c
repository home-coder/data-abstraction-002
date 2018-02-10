/*************************************************************************
 > Filename   : malloc.c
 > Author     : oneface - one_face@sina.com
 > Company    : 江山如画
 > Time       : 2018-02-10 11:32:38
 ************************************************************************/

/*
	证明malloc申请的是连续的内存空间
	因为p 指向的内存中数据为*(p+i), 地址为p+i, 查看p+i是连续的
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int i;
	char *p = (char *)malloc(sizeof(char) * 10);

	for (i = 0; i < 10; i++) {
		printf("p[%d] = %p\n", i, p + i);
	}

	memcpy(p, "0123456789", 10);

	for (i = 0; i < 10; i++) {
		printf("%c %p\n", *(p+i), &*(p + i));
		printf("%c %p\n", *(p+i), p + i);
	}

	/*********栈**************/
	char q[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (i = 0; i < 10; i++) {
		printf("%d %p\n", q[i], &q[i]);
		printf("%c %p\n", q[i], &q[i]);
	}

	return 0;
}
