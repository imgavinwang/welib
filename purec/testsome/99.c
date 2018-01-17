#include<stdio.h>
#include <stdlib.h>

void mtable_helper(int const n, int const i)
{
   if(i > n)
   {
     printf("\n");
   }
   else
   {
	   printf("%dx%d=%d ", i, n, i *n); 
	   mtable_helper(n,i+1);
   } 
}

void mtable(int const n)
{
  if(0 == n) return;
  mtable(n-1);
  mtable_helper(n,1);
}

void print99()
{
    int i;
	i=0;
	for(i=11;i<100;i++)
	{
		if(i%10==0||i%10>i/10)
		{
			printf("\n");
			i=i/10*10+10+1;
		}
		printf("%d*%d=%d ",i/10,i%10,(i/10)*(i%10));
	}
}

int print99_1()
{
	int a;
	
	for (a = 0x11; a < 0xa0; a++)
	{
		for (a = (a & 0xf0) + 1; (a & 0x0f) <= ((a & 0xf0) >> 4); a++)
		{
			printf("%dx%d=%d\t",
				(a & 0x0f),
				(a & 0xf0) >> 4,
				((a & 0xf0) >> 4) * (a & 0x0f));
		}
		a += 0x10;
		printf("\n");
	}
	
	return 0;
}


void main()
{
    mtable(9);//递归
	print99();//个位十位
	print99_1();高低位
}
