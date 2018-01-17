#include <stdio.h>

void selectSort(int a[], int n)
{
	for(int i=0; i<n;i++) {
		int min = i;
		for(int j=i+1;j<n;j++) {
			if(a[j] < a[min]) min=j;
		}
		if(min != i) {
			int tmp = a[i];
			a[i] = a[min];
			a[min] = tmp;
		}
	}
}

void printArray(int a[], int n)
{
	for(int i=0; i<n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	int a[] = {1,8,4,5,7,2};
	printArray(a, 6);
	selectSort(a, 6);
	printArray(a, 6);
}
