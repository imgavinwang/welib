//C++0x之后该实现是线程安全的，有兴趣可以读相关的标准草案（section 6.7），编译器的支持程度不一定，但是G++4.0及以上是支持的。

class Singleton  
{  
    public:  
        static Singleton& Instance()      //Instance()作为静态成员函数提供里全局访问点  
        {  
            static Singleton instance;  
            return instance;  
        }  
  
    private:  
        Singleton();                     //这里将构造，析构，拷贝构造，赋值函数设为私有，杜绝了生成新例  
        ~Singleton();  
        Singleton(const Singleton&);  
        Singleton& operator=(const Singleton&);       
};
