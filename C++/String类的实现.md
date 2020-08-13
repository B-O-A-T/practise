```C++
class String
{
public:
       String(const char *str = NULL); // 通用构造函数
       String(const String &another); // 拷贝构造函数
       ~ String(); // 析构函数
       String & operater =(const String &rhs); // 赋值函数
private:
       char *m_data; // 用于保存字符串
};
String::String(const char *str)
{
       if ( str == NULL ) //strlen在参数为NULL时会抛异常才会有这步判断
       {
              m_data = new char[1] ;
              m_data[0] = '/0' ;
       }
       else
       {
              m_data = new char[strlen(str) + 1];
              strcpy(m_data,str);
       }
 
}
 
String::String(const String &another)
{
       m_data = new char[strlen(another.m_data) + 1];
       strcpy(m_data,another.m_data);
}
 
String& String::operator =(const String &rhs)
{
       if ( this == &rhs)
              return *this ;
       delete []m_data; //删除原来的数据，新开一块内存
       m_data = new char[strlen(rhs.m_data) + 1];
       strcpy(m_data,rhs.m_data);
       return *this ;
}
 
String::~String()
{
       delete []m_data ;
}
```

什么函数不能声明为虚函数？

一、首先回顾下什么是虚函数及其作用，以便更好理解什么函数不能声明或定义为虚函数：
\1. 定义：
虚函数必须是基类的非[静态成员](https://link.zhihu.com/?target=http%3A//baike.baidu.com/view/534160.htm)函数，其访问权限可以是protected或public，在基类的类定义中定义虚函数的一般形式：
　　virtual 函数返回值类型 虚函数名（形参表）　　{ 函数体 }
\2. 作用：
虚函数的作用是实现[动态联编](https://link.zhihu.com/?target=http%3A//baike.baidu.com/view/535555.htm)，也就是在程序的运行阶段动态地选择合适的成员函数，在定义了虚函数后，可以在基类的[派生类](https://link.zhihu.com/?target=http%3A//baike.baidu.com/view/535532.htm)中对虚函数重新定义，在派生类中重新定义的函数应与虚函数具有相同的形参个数和形参类型，以实现统一的接口，不同定义过程。如果在派生类中没有对虚函数重新定义，则它继承其基类的虚函数。
当程序发现虚函数名前的关键字virtual后，会自动将其作为动态联编处理，即在程序运行时动态地选择合适的成员函数。
\3. 使用方法：
动态联编规定，只能通过指向基类的指针或基类对象的引用来调用虚函数，其格式：
　　指向基类的指针变量名->虚函数名（实参表）
或
基类对象的引用名. 虚函数名（实参表）
\4. 其它说明：　　
虚函数是C++多态的一种表现：
例如：子类继承了父类的一个函数（方法），而我们把父类的指针指向子类，则必须把父类的该函数（方法）设为virtual（虚函数)。　　使用虚函数，我们可以灵活的进行动态绑定，当然是以一定的开销为代价。 如果父类的函数（方法）根本没有必要或者无法实现，完全要依赖子类去实现的话，可以把此函数（方法）设为virtual 函数名=0 我们把这样的函数（方法）称为纯虚函数。　　如果一个类包含了纯虚函数，称此类为[抽象类](https://link.zhihu.com/?target=http%3A//baike.baidu.com/view/262290.htm) 。
二、什么函数不能声明为虚函数：
一个类中将所有的成员函数都尽可能地设置为虚函数总是有益的。
设置虚函数须注意：
1：只有类的成员函数才能说明为虚函数；
2：静态成员函数不能是虚函数；
3：内联函数不能为虚函数；
4：构造函数不能是虚函数；
5：析构函数可以是虚函数，而且通常声明为虚函数。
类里面“定义”的成员函数是内联的，但是仍然可以成为虚函数，那么是不是可以说“内联函数不能成为虚函数”这句话有问题呢，是不是应该改成“显式定义的内联函数不能成为虚函数”。



const意味着“只读”就可以了