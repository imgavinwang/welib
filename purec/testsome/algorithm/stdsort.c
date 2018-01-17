#include <stdio.h>
#include <iostream>
#include <algorithm>
/*
Musser在1996年发表了一遍论文，提出了Introspective Sorting(内省式排序)，
它是一种混合式的排序算法：
1)在数据量很大时采用正常的快速排序，此时效率为O(logN)。
2)一旦分段后的数据量小于某个阈值，就改用插入排序，因为此时这个分段是基本有序的，这时效率可达O(N)。
3)在递归过程中，如果递归层次过深，分割行为有恶化倾向时，它能够自动侦测出来，使用堆排序来处理，
在此情况下，使其效率维持在堆排序的O(N logN)，但这又比一开始使用堆排序好。
由此可知，它乃综合各家之长的算法。也正因为如此，C++的标准库就用其作为std::sort的标准实现。
*/
using namespace std;

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
    sort(a, a+6, std::less<int>());
    printArray(a, 6);
}
