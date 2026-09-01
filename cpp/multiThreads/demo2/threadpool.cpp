#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <chrono>
#include <functional>

class ThreadPool
{
public:
	explicit ThreadPool(size_t threads): stop_(false)
	{
		for (size_t i = 0; i < threads; ++i)
		{
			workers_.emplace_back(&ThreadPool::worker_loop, this);
		}
	}

	template<typename F, typename... Args>
	auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
	{
		using return_type = typename std::result_of<F(Args...)>::type;

		auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

		std::future<return_type> res = task->get_future();

		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			if (stop_)
			{
				throw std::runtime_error("enqueue on stopped ThreadPool");
			}
			tasks_.emplace([task](){ (*task)(); });
		}

		condition_.notify_one();
		return res;
	}

	~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			stop_ = true;
		}

		condition_.notify_all();
		for (std::thread& worker: workers_)
		{
			if (worker.joinable())
			{
				worker.join();
			}
		}
	}

	size_t pending_tasks() const
	{
		std::unique_lock<std::mutex> lock(queue_mutex_);
		return tasks_.size();
	}

	size_t size() const
	{
		return workers_.size();
	}
private:
	void worker_loop()
	{
		while (true)
		{
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> lock(queue_mutex_);
				condition_.wait(lock, [this]{
						return stop_ || !tasks_.empty();
						});

				if (stop_ && tasks_.empty())
				{
					return;
				}

				task = std::move(tasks_.front());
				tasks_.pop();
			}

			task();
		}
	}

	std::vector<std::thread> workers_;
	std::queue<std::function<void()>> tasks_;

	mutable std::mutex queue_mutex_;
	std::condition_variable condition_;
	bool stop_;

};


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
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

