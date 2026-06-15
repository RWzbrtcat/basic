#include <iostream>
#include <exception>  // 包含头文件

/*
  std::terminate()是C++标准库的程序终止函数，作用：立即、无条件终止整个程序。
  程序遇到无法处理的致命错误 -> 调用 terminate() -> 程序直接退出
*/

// 特点
// 1.默认行为
// 1.1 调用 std::abort() 终止程序
// 1.2 通常会出发程序崩溃/终端
// 2. 不可恢复 - 一旦调用，程序无法继续运行
// 3. 不保证析构 - 默认情况下不会执行栈展开，局部对象可能不被析构


// 代码示例1. 未捕获异常 -> 触发 terminate

/*
void func()
{
	throw "抛出异常，但并未捕获"; // no catch
}

int main()
{
	func();
	return 0;
}
*/

// 代码示例2. 构造函数抛异常 -> 触发terminate


class Demo{
public:
	Demo(){
		std::cout << "Constructor starts" << "\n";
		throw "Constructor error";
		std::cout << "Constructor ends" << "\n";
	}
	~Demo(){
		std::cout << "Destructor" << "\n";
	}
};

int main()
{
	try{
		Demo demo;
		throw "normal";
	} catch (const char* msg){
		std::cout << "Caught: " << msg << "\n";
	} catch (...){
		std::cout << "Caught something else" << "\n";
	}

	return 0;
}



