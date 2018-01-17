#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

int binarySearch(vector<int> &v, int key)
{
	int low = 0, high = v.size() - 1;
	while(low <= high){
		int middle = (low + high) / 2;
		if(v[middle]== key) 
			return middle;
		else
			v[middle] > key ? high = middle - 1 : low = middle + 1;
	}
	return -1;
}

int main()
{
	int a[] = {1,4,6,8,9,10,11};
    vector<int> v(a, a+7);
	printf("%d\n", binarySearch(v, 8));
}
