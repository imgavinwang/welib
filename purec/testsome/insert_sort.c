#include <stdio.h>
#include <stdlib.h>

/*
算法描述如下：
⒈ 从第一个元素开始，该元素可以认为已经被排序
⒉ 取出下一个元素，在已经排序的元素序列中从后向前扫描
⒊ 如果该元素（已排序）大于新元素，将该元素移到下一位置
⒋ 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
⒌ 将新元素插入到下一位置中
⒍ 重复步骤2~5
*/
void print_array(int *array, int n)
{
	for(int i=0;i<n;i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void insert_sort(int*array,unsigned int n)
{
	int i,j;
	int temp;
	for(i=1;i<n;i++)
	{
		temp=*(array+i);
		for(j=i;j>0 && *(array+j-1)>temp;j--)
		{
			*(array+j)=*(array+j-1);
		}
		*(array+j)=temp;
		print_array(array, n);
	}
}



int main()
{
	int a[] = {5,1,7,3,1,6,9,4};
	print_array(a, 8);
	insert_sort(a, 8);
}