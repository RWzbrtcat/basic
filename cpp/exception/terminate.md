

## 什么情况下会自动调用 terminate()

1. 异常没有被任何`catch`捕获

2. 栈展开期间，析构函数抛出异常

3. `noexcept`函数内抛出异常

4. 主动调用`std::terminate()`



## 自定义`terminate`行为

可以使用`set_terminate()`替换默认行为，例如：
- 打印日志
- 保存数据
- 做最后的清理工作 
