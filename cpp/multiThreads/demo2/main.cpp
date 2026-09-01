#include <iosrteam>
#include <chrono>

int main()
{
	ThreadPool pool(4);

	std::vector<std::future<int>> results;
	int task_number;
	std::cout << "please input the worker number: ";
	std::cin >> task_number;
	for (int i = 0; i < task_number; ++i)
	{
		results.emplace_back(
				pool.enqueue([i]{
					std::this_thread::sleep_for(std::chrono::miliseconds(100));
					std::cout << "Task: " << i << " executed by thread " << std::this_thread::get_id() << std::endl;
					return i * i;
				})
				);
	}

	for (auto& result : results)
	{
		std::cout << "Result: " << result.get() << std::endl;
	}
	std::cout << "Pending Tasks: " << pool.pending_tasks() << std::endl;
	return 0;
}

