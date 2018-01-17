#include <stdio.h>

int binSearch(int array[], int n, int key)
{
	int low = 0, high = n - 1;
	while(low <= high){
		int middle = (low + high) / 2;
		if(array[middle] == key) 
			return middle;
		else
			array[middle] > key ? high = middle - 1 : low = middle + 1;
	}
	return -1;
}

int binSearchRecurse(int array[], int low, int high, int key)
{
	if(low <= high) {
		int middle = (low + high) / 2;
		if(array[middle] == key)
			return middle;
		else if(array[middle] > key)
			return binSearchRecurse(array, low, middle - 1, key);
		else
			return binSearchRecurse(array, middle + 1, high, key);
	}
	return -1;
}

int main()
{
	int a[] = {1,4,6,8,9,10};
	//int result = binSearchRecurse(a, 0, 5, 6);
	int result = binSearch(a, 6, 6);
	printf("%d\n", result);
}
