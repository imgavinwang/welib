#include <stdio.h>

void printArray(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int shellSort(int a[], int n)
{
	int tmp, k;
	for(int gap = n / 2; gap > 0; gap /= 2) {
		for(int i = 0; i < n; i++) {
			for(int j = i + gap; j < n; j += gap) {
				tmp = a[j];
				for(k = j; k > 0 && a[k - gap] > tmp; k--) {
					a[k] = a[k - 1];
				}
				a[k] = tmp;
			}
		}
	}
}

int main()
{
	int a[] = {4,6,3,2,7,9,1,5};
	printArray(a, 8);
	shellSort(a, 8);
	printArray(a, 8);
}