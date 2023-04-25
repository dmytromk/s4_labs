#pragma once
#include <vector>

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
double time_evaluation(function func, Args ...args)
{
	std::clock_t start = std::clock();
	func(args...);
	return static_cast<double>(std::clock() - start);
}

//template <typename F, typename ... Ts>
//double time_evaluation(F&& f, Ts&&...args)
//{
//	std::clock_t start = std::clock();
//	std::forward<F>(f)(std::forward<Ts>(args)...);
//	return static_cast<double>(std::clock() - start);
//}