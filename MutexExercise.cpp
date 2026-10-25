#include <vector>
#include <iostream>
#include <thread>
#include <numeric>
#include <mutex>

int main()
{
	std::vector<int> v;
	const int numberCount = 1e6;
	v.resize(numberCount);
	std::iota(v.begin(), v.end(), 0);
	const int threadCount = 10;
	std::vector<std::thread> workers;
	long long int result = 0;
	std::mutex resultMutex;
	for (int threadId = 0; threadId < threadCount; threadId++)
	{
		int numbersPerThread = numberCount / threadCount;
		int from = threadId * numbersPerThread;
		int to = (threadId + 1) * numbersPerThread;
		auto sumNumbersFromTo = [threadId, from, to, &v, &result, &resultMutex]()
			{
				printf("Thread Id %d starts on numbers %d to %d \n", threadId, from, to);

				long long int sum = 0;
				for (int i = from; i < to; i++)

				{
					sum += v[i];
				}
				std::cout << "Thread Id " << threadId << " is done with a sum of " << sum << '\n';
				std::lock_guard<std::mutex> lock(resultMutex);
				result += sum;
			};

		std::thread worker(sumNumbersFromTo);
		workers.push_back(std::move(worker));
	}
	for (int i = 0; i < threadCount; i++)
	{
		workers[i].join();
	}
	std::cout << result;
}