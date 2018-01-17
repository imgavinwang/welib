#include <iostream>
using namespace std;

//阶梯访问表，二分查找
const char gradeTable[] = {
    'A', 'B', 'C', 'D', 'F'
};

const int DONWLIMIT_LENGTH = 4;

const int downLimit[] = {
    90, 80, 70, 60
};


int BinarySearch(int score)
{
    int low = 0;
    int high = DONWLIMIT_LENGTH - 1; //downLimit的最大的Index
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(score < downLimit[mid])
        {
            low = mid + 1;
        }
        else if(score > downLimit[mid])
        {
            high = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return low;
}

int main()
{
    int score = 87;
    int gradeLevel = BinarySearch(score);
    cout << "等级为 " << gradeTable[gradeLevel] << endl;
    return 0;
}
