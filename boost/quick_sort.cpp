#include <iostream>
#include <stack>

using namespace std;

int partion(int* root,int low,int high)
{
    int part=root[low];
    while(low<high) {
        while(low<high&&root[high]>part) high--;
        root[low]=root[high];
        while(low<high&&root[low]<part) low++;
        root[high]=root[low];
    }
    root[low]=part;
    return low;
}

void quickSort2(int* root,int low,int high)
{
    stack<int> st;
    int k;
    if(low<high) {
        st.push(low);
        st.push(high);
        while(!st.empty()) {
            int j=st.top();st.pop();
            int i=st.top();st.pop();

            k=partion(root,i,j);

            //其实就是用栈保存每一个待排序子串的首尾元素下标，下一次while循环时取出这个范围，对这段子序列进行partition操作
            if(i<k-1) {
                st.push(i);
                st.push(k-1);
            }
            if(k+1<j) {
                st.push(k+1);
            st.push(j);
            }
        }
    }
}

int main()
{
    int a[8]={4,2,6,7,9,5,1,3};
    quickSort2(a,0,7);
    
    int i;
    for(i=0;i<8;i++)
        cout<<a[i]<<" ";
    cout<<endl;

    return 0;
}
