#include <vector>
#include <iostream>
using namespace std;

int quicksort(vector<int> &v, int left, int right){
	if(left < right){
		int key = v[left];
		int low = left;
		int high = right;
		while(low < high){
			while(low < high && v[high] > key){
				high--;
			}
			v[low] = v[high];
			while(low < high && v[low] < key){
				low++;
			}
			v[high] = v[low];
		}
		v[low] = key;
		quicksort(v,left,low-1);
		quicksort(v,low+1,right);
	}
}

void print_vector(vector<int> &v)
{
	vector<int>::iterator iter;  
	for (iter=v.begin();iter!=v.end();iter++) {  
		cout<<*iter<<' ';
	}
	cout << "\n";
}

int main()
{
	int a[]={57,68,59,52,72,28,96,33,24};

	vector<int> v(a, a+9);
	print_vector(v);
	quicksort(v, 0, 8);
	print_vector(v);	
}
