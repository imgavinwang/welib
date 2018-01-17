#include <stdio.h>
#include <vector>
#include <string>
#include <stack>
#include <ctype.h>
#include <map>
#include <iostream>
using namespace std;

#define INT_MIN     (-2147483647 - 1)
#define INT_MAX      2147483647

class Solution {
public:
    int trailingZeroes(int n) {
        int x = 5;
        int ans = 0;
        while(n >= x){
            ans += n / x;
            x *= 5;
        }
        return ans ;
    }

    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int, int> m;
        vector<int> result;
        for(int i=0; i<numbers.size(); i++){
            // not found the second one
            if (m.find(numbers[i])==m.end() ) { 
                // store the first one poisition into the second one's key
                m[target - numbers[i]] = i; 
            }else { 
                // found the second one
                result.push_back(m[numbers[i]]+1);
                result.push_back(i+1);
                break;
            }
        }
        return result;
    }

    /*
    string lengthOfLongestSubstring(string s) {
        map<string, int> m;

        for(int i=0; i<s.sizeof(); i++) {
            string max=MaxSub(s.substr(0,s.sizeof()));
            int max_len=max.sizeof();
            if(m.find(max)==m.end()) {
                m[max]=max.sizeof();
            } else {
                if(m[max]>max.sizeof()) m[max]=max.sizeof();
            }
        }


        
    }
    */

    int lengthOfLongestSubstring(string s) {
        map<char, int> m;
        int maxLen = 0;
        int startPos = 0;
        int lastRepeatPos = -1;
        for(int i=0; i<s.size(); i++){
            if (m.find(s[i])!=m.end() && lastRepeatPos < m[s[i]]) {
                lastRepeatPos = m[s[i]];
            }
            if ( i - lastRepeatPos > maxLen ){
                maxLen = i - lastRepeatPos;
                startPos = i;
                cout << s.substr(startPos, maxLen) << maxLen << endl;
            }
            m[s[i]] = i;
        }
        cout << s.substr(startPos, maxLen) << endl;
        return maxLen;
    }

    string zigZagConversion(string s, int nRows) {
        //The cases no need to do anything
        if (nRows<=1 || nRows>=s.size()) return s;
         
        vector<string> r(nRows);
        int row = 0;
        int step = 0;
        for(int i=0; i<s.size(); i ++) {
            if (row == nRows-1) step = -1;
            if (row == 0) step = 1;
            //cout << row <<endl;
            r[row] += s[i];
            row += step;
        }
        
        string result;
        for (int i=0; i<nRows; i++){
            result += r[i];
        }
        return result;
    }

    int reverseInteger(int x) {
        if (x > 2147483647 || x < -2147483648) return 0;
        int y = 0;
        int n = 0;
        while(x != 0) {
            if (y > 2147483647 || y < -2147483648) return 0;
            n = x % 10;
            y = y * 10 + n;
            x = x / 10;
        }
        return y;
    }

    int atoi(const char *str) {
        if (str==NULL || *str=='\0'){
            return 0;
        }
        
        long ret=0;
        
        for(;isspace(*str); str++);
        
        bool neg=false;
        if (*str=='-' || *str=='+') {
            neg = (*str=='-') ;
            str++;
        }
        
        for(; isdigit(*str); str++) {
            int digit = (*str-'0');
            /*
            if(neg){
                if( -ret < (INT_MIN + digit)/10 ) {
                    return INT_MIN;
                }
            }else{
                if( ret > (INT_MAX - digit) /10 ) {
                    return INT_MAX;
                }
            }
            */
    
            ret = 10*ret + digit ;
        }
        
        return neg?(int)-ret:(int)ret;
    }
};

void atoi_test()
{
    Solution a;
    int result = a.atoi("2147483648");
    printf("%d\n", result);
}

void reverseInteger_test()
{
    Solution a;
    int x = 2147483647;
    cout << x << " : " << a.reverseInteger(x);
}

void zigZagConversion_test()
{

    Solution a;
    string s;
    int r;

    s = "IAMGAVINWANG";
    cout << s << " : " << a.zigZagConversion(s, 4) << endl;
}

void twoSumTest()
{
    Solution s;
    vector<int> v;
    v.push_back(2);
    v.push_back(8);
    v.push_back(7);
    v.push_back(15);
    vector<int> t = s.twoSum(v, 9);
    for(int i=0; i<t.size(); i++) {
        printf("%d ", t[i]);
    }
}

void lengthOfLongestSubstringTest()
{
    Solution a;
    string s = "abcabcbb";
    cout << s << " : " << a.lengthOfLongestSubstring(s) << endl;

    s = "bbbbb";
    cout << s << " : " << a.lengthOfLongestSubstring(s) << endl;

    s = "bbabcdb";
    cout << s << " : " << a.lengthOfLongestSubstring(s) << endl;
}

int singleNumber(int A[], int n) 
{ 
     int s = 0; 
     for(int i=0; i<n; i++){ 
         s = s^A[i]; 
     } 
     return s; 
 } 
 



int main()
{
    Solution s;
    int result = s.trailingZeroes(11);
    //printf("%d\n", result);

    //twoSumTest();

    //lengthOfLongestSubstringTest();

    //zigZagConversion_test();

    //reverseInteger_test();

    //atoi_test();

    int a[]={1,2,1,2,3}; 
    printf("%d\n", singleNumber(a,5)); 

    return 0;
}
