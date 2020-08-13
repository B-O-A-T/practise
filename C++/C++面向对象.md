##### 类型系统

定义：在编程语言中，“类型系统”是将“type”属性指定给不同计算机程序构造块的**规则集**。

- 这些类型规范并强制程序员用于数据结构和组件的其它隐式类别（e.g. “string”， “array of float","function returning boolean"）

意义：减少程序中可能出现的bug

1. 定义不同程序块间的接口
2. 检查多个块之间是否以一致的方式连接在一起



静态类型，上述检查若发生在编译期：C，C++

动态类型，上述检查若发生在运行时：python

上述检查若同时存在于编译期和运行时，称为混合类型



##### auto 关键字

1. auto变量必须在定义初始化，这类似于const关键字
2. 定义在一个auto序列的变量必须始终推导成同一类型
3. 如果初始化表达式是引用或 const，则去除引用或const语义

```CPP
int a{10}; int &b = a;
auto c = b; //c的类型为int而非int&（去除引用）
const int a1{10};
auto b1 = a1; //b1的类型为int而非const int（去除const）
```

4. 如果auto关键字带上&号，则不去除引用或const语义

```CPP
int a = 10; int &b = a;
auto& d = b; //此时d的类型才为int&
const int a2 = 10;
auto& b2 = a2; //因为auto带上&，故不去除const，b2类型为const int
```

5. 初始化表达式为数组时，auto关键字推导类型为指针。

```CPP
int a3[3] = { 1, 2, 3 };
auto b3 = a3;
cout << typeid(b3).name() << endl; //输出int * （输出与编译器有关）
```

6. 若表达式为数组且auto带上&，则推导类型为数组类型。 

```CPP
int a7[3] = { 1, 2, 3 };
auto& b7 = a7;
cout << typeid(b7).name() << endl; //输出int [3] （输出与编译器有关）
```

7. C++14中，auto可以作为函数的返回值类型和参数类型



```CPP
auto x[] = {1,2,3}; // 错误，auto不能出现在顶级数组类型中
```



##### decltype 关键字

decltype利用已知类型声明新变量。
有了auto，为什么还要整出一个decltype？原因是，我们有时候想要从表达式的类型推断出要定义的变量类型，但不想用该表达式的值初始化变量。	
decltype是在编译期推导一个表达式的类型，它只做静态分析，因此它不会导致已知类型表达式执行。
decltype 主要用于泛型编程（模板）

```CPP
#include<iostream>
using namespace std;
int  fun1()  { return 10;  }
auto fun2()  { return 'g'; }  // C++14
int main(){
    // Data type of x is same as return type of fun1()
    // and type of y is same as return type of fun2()
    decltype(fun1()) x;  // 不会执行fun1()函数
    decltype(fun2()) y = fun2();
    cout << typeid(x).name() << endl;
    cout << typeid(y).name() << endl;
    return 0;
}
```



###### decltype与auto的对比

- auto忽略最上层的const，decltype则保留最上层的const
- auto忽略原有类型的引用，decltype则保留原有类型的引用
- 对解引用操作，auto推断出原有类型，decltype推断出引用
- auto推断时会实际执行，decltype不会执行，只做分析。

总之在使用过程中和const、引用和指针结合时需要特别小心。