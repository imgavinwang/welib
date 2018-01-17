#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        if(str.empty()) return 0;
        int len = str.length();
        long res = 0;
        int tag = 1, i = 0; // tag标记正负号
        while(i < len && str.at(i) == ' ') i ++; // 除去空格
        if(i == len) 
            return 0; // 全为空格的情况
        else if(str.at(i) == '-') { // 负号
            tag = -1;
            i ++;
        } else if(str.at(i) == '+') { // 正号
            i ++;
        }
        while(i < len) {
            if(str.at(i) < '0' || str.at(i) > '9') { // 碰到第一个非法字符，返回现在有效的数字
                return (int)res;
            }
            res = res * 10 + tag * (str.at(i) - '0'); // 乘以tag，区分正负数
            if(res > INT_MAX) return INT_MAX; // 上溢出时，返回最大整数
            else if(res < INT_MIN) return INT_MIN; // 下溢出时，返回最小整数
            i ++;
        }
        int num = (int)res;
        return num;
    }
};

int main()
{
    Solution a;
    cout << a.myAtoi("5a")  << endl;
    return 0;
}