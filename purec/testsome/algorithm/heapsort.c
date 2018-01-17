#include <stdio.h>

void printArray(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void swap(int a, int b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

//  从i节点开始调整,n为节点总数 从0开始计算 i节点的子节点为 2*i+1, 2*i+2
void MinHeapFixdown(int a[], int i, int n)
{
    int j, temp;

	temp = a[i];
	j = 2 * i + 1;
	while (j < n)
	{
		if (j + 1 < n && a[j + 1] < a[j]) //在左右孩子中找最小的
			j++;

		if (a[j] >= temp)
			break;

		a[i] = a[j];     //把较小的子结点往上移动,替换它的父结点
		i = j;
		j = 2 * i + 1;
	}
	a[i] = temp;
}

//在最小堆中删除数
void MinHeapDeleteNumber(int a[], int n)
{
	swap(a[0], a[n - 1]);
	MinHeapFixdown(a, 0, n - 1);
}

void MinheapsortTodescendarray(int a[], int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		swap(a[i], a[0]);
		MinHeapFixdown(a, 0, i);
	}
}

int main()
{
	int a[] = {4,6,3,2,7,9,1,5};
	printArray(a, 8);
	MinheapsortTodescendarray(a, 8);
	printArray(a, 8);
}
