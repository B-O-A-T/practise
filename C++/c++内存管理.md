## c++内存管理

| 分配                     | 释放                       | 类型      | 可否重载                 |
| :----------------------- | -------------------------- | --------- | ------------------------ |
| malloc()                 | free()                     | C函数     | 不可                     |
| new                      | delete                     | C++表达式 | 不可                     |
| ::operator new()         | ::operator delete()        | C++函数   | 可                       |
| allocator<T>::allocate() | allocator<T>::deallocate() | C++标准库 | 可自由设计以搭配任何容器 |

new

定位new

![img](https://ivanzz1001.github.io/records/assets/img/cplusplus/cpp_new_malloc.jpg)