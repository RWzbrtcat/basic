

# new/delate And malloc/free

## 一、基本区别

1. malloc/free 是 C 标准库函数；new/delete 是 C++ 关键字。

2. malloc/free 无类型检查（返回 void`*`，需显示强制转换）；new/delete 类型安全（返回具体类型指针）。

3. malloc/free 不调用构造函数/析构函数；new/delete 自动调用析构函数。

4. malloc/free 内存分配失败返回 NULL；new/delete 默认抛出 std::bad`_`alloc异常。

5. malloc/free 不可重载；new/delete 可重载。

6. malloc/free 需手动计算分配的内存大小；new/delete 自动根据类型大小判断。

7. malloc/free 不涉及异常；new/delete 支持异常安全。


## 二、实现机制

### 1、malloc/free 的底层实现

#### 1.1 内存分配流程

- 调用 malloc(size)

1. 查找空闲块：从空闲链表中查找足够大的内存块。

2. 分割块：若找到的块大于所需大小，则分割为已分配块和剩余空闲块。

3. 标记为已使用：更新元数据（如大小、使用状态）。

4. 返回地址：返回指向可用内存的指针。

- 调用 free(ptr)

1. 标记为可用：将内存块状态设为“空闲”。

2. 合并相邻块：与前后空闲块合并，减少碎片。

3. 更新链表：将块插入空闲链表合适位置。


#### 1.2 内存回收去向

- 归还给内存管理器：free 后的内存被放入空闲链表，后续 malloc 可能复用。
- 一般不会立即归还给操作系统（保留内存以提高性能）。若释放的内存块足够大（如超过 mmap 阈值），可能通过 munmap 归还。


### 2. new/delete 的底层实现

#### 2.1 new 的执行流程

```cpp
int* p = new int(10);
```

- 步骤
1. 调用 operator new（默认调用 malloc ）。
2. 构造对象：调用 int 的构造函数（内置类型无操作）
3. 返回指针：返回指向 int 的指针
 
#### 2.2 delete 的执行流程

```cpp
delete p;
```

- 步骤
1. 析构对象：调用 int 的析构函数（内置类型无操作）。
2. 调用 operator delete（默认调用 free）。


#### 2.3 new[]/delete[] 的特殊处理

```cpp
int* arr = new int[10];
delete[] arr;
```

- new[] 在分配内存时会多分配 4~8 字节（取决于平台），用于存储数组长度以及 delete[] 时调用每个元素的析构函数。
- delete[] 读取数组长度，逐个调用析构函数，最终调用 operator delete[]（默认调用 free ）。

#### 2.4 重载 operator new / operator delete

允许为特定类或全局重载，实现自定义内存池、日志记录、内存对齐等功能。

```cpp
void* operator new(size_t size)
{
    void* ptr = malloc(size);
    if (!ptr) throw std::bad_alloc();
    return ptr;
}
```



