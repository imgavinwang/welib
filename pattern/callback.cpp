// cbBysink.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cbBysink.h"

/************************************************************************/
/*                上层回调函数                                            */
/************************************************************************/

 class CMyWork : public baseCallBack
 {
 public:
     CMyWork()
     {
         // 注册回调
         CWork::registercallback(this);
     }
     // 回调注册实现
     void CallbackFunction(int a, int b)
     {
         cout << "a = " << a << ",b = " << b << "\n" << endl;
         return;
     }
     // 触发回调
     void makefunction(int a, int b)
     {
         CWork::makecallback(a, b);
         return;
     }
 protected:
 private:
 };

 int main(int argc, char* argv[])
 {
     CMyWork c_mywork;

     // 触发的时候不需要进行动态注册
     c_mywork.makefunction(5, 6);

     return 0;
 }