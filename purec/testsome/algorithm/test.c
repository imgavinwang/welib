#include <stdio.h>

int main()
{
	int i = 0, sum = 0;
	for(i=0; i<10; sum+=i,++i) ;
	printf("%d %d\n",i, sum);
}