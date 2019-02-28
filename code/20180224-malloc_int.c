#include <stdio.h>
#include <stdlib.h>
int
main(void)
{
	int *p=malloc(sizeof(int));
	*(p-1)=-1;
	free(p);
	return 0;
}



