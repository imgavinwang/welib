#include <iostream>
#include <string>
#include <limits.h>

using namespace std;
class Solution{
public:
	int myAtoi(string str) {
		if(str.empty()) return 0;

		int len = str.length();
		long value = 0;
		int tag = 1, i = 0;

		while(i < len && str.at(i) == ' ') i++;
		if(i == len) return 0;
		if(str.at(i) == '-') {
			tag = -1;
			i++;
		} else {
			i++;
		}

		while(i < len) {
			if(str.at(i) < '0' || str.at(i) > '9') return (int)value;

			value = value * 10 + tag * (str.at(i) - '0');
			if(value > INT_MAX) return INT_MAX;
			else if(value < INT_MIN) return INT_MIN;
			i++;
		}

		return (int)value;
	}
};

int main()
{
    Solution a;
    cout << a.myAtoi("5a")  << endl;
    return 0;
}
