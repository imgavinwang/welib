#include <stdio.h>

void insert_sort(int a[], int n)
{
	int i,j;
	int temp;
	for(i=1;i<n;i++)
	{
		temp=a[i];
		for(j=i; j>0 && a[j-1] > temp; j--)
		{
			a[j]=a[j-1];
		}
		a[j]=temp;
	}
}

void print_a(int *a, int n)
{
	for(int i=0;i<n;i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	int a[] = {5,1,7,3,1,6,9,4};
	print_a(a, 8);
	insert_sort(a, 8);
	print_a(a, 8);
}
