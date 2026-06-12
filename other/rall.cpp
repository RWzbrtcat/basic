#include <iostream>
#include <fstream>

#include <thread>
#include <mutex>

#include <memory>

/*
   RALL (Resource Acquisition Is Initialization) 资源获取即初始化
   1. 资源获取即初始化，资源的分配与对象的初始化绑定在一起，资源的释放与对象的销毁绑定在一起
   2. 自动释放资源
 */

// 应用示范
// 1. 文件管理，通过 std::fstream 自动管理文件的打开和关闭


void readFile(const std::string& file_name)
{
	// 文件在构造时打开，在析构时关闭
	std::ifstream file(file_name);

	if (!file.is_open())
	{
		std::cerr << "can not open file!" << "\n";
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << "\n";
	}
	return; // 文件在作用域结束时自动关闭
}


// 2. 互斥锁管理，通过 std::lock_guard/std::unique_lock 自动管理锁的获取和释放

std::mutex mtx;

void whichThread(int id)
{
	// std::lock_gurad 自动管理互斥锁
	std::lock_guard<std::mutex> lock(mtx); // 自动上锁
	std::cout << "Thread's id is " << id << "\n";
	return; // 自动解锁
}

// 3. 内存管理，通过智能指针自动管理堆内存

class Demo{
public:
	Demo(int val) : value(val){
		std::cout << "Constructor" << "\n";
	}
	~Demo(){
		std::cout << "Destructor" << "\n";
	}
	void display(){
		std::cout << "Display " << value << "\n";
	}

private:
	int value;

};



int main()
{
	// 文件管理示例
	readFile("test.txt");

	// 互斥锁管理示例
	std::thread t1(whichThread, 1);
	std::thread t2(whichThread, 2);

	t1.join();
	t2.join();
	
	// 内存管理示例
	std::unique_ptr<Demo> demo(new Demo(3));
	demo->display();

	return 0; // demo 自动析构
}
