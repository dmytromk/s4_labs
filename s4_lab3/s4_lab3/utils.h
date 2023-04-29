#pragma once
#include <vector>
#include <chrono>


std::vector<int> randomize(int size, int modulo = 10000)
{
	std::vector<int> result;
	for (int i = 0; i < size; i++)
	{
		result.push_back(rand() % modulo);
	}
	return result;
}


template <typename function, typename ... Args>
long long time_evaluation(function&& func, Args&&...args)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::forward<function>(func)(std::forward<Args>(args)...);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_result = end - start;;
	return ms_result.count();
}