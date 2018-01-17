#include <stdio.h>


void printArray(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int quickSort(int a[], int left, int right)
{
	if(left >= right) return 0;
	int low = left, high = right;
	int key = a[low];
	while(low < high) {
		while(low < high && a[high] > key) high--;
		a[low] = a[high];
		while(low < high && a[low] < key) low++;
		a[high] = a[low];
	}
	a[low] = key;
	printArray(a, 8);
	quickSort(a, left, low - 1);
	quickSort(a, low + 1, right);
}


int main()
{
	int a[] = {4,6,3,2,7,9,1,5};
	printArray(a, 8);
	quickSort(a, 0, 7);
	printArray(a, 8);
}