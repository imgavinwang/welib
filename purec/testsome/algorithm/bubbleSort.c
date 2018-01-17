#include <stdio.h>

void bubbleSort(int a[], int n)
{
	for(int i=0; i<n-1; i++) {
		for(int j=0; j<n-1-i; j++) {
			if(a[j] > a[j+1]) {
				int tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}

void printa(int a[], int n)
{
	for(int i=0; i<n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	int a[] = {1,8,4,5,7,2};
	printa(a, 6);
	bubbleSort(a, 6);
	printa(a, 6);
}