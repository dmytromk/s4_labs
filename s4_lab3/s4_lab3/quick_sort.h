#pragma once
#include <iostream>
#include <vector>
#include <thread>

std::vector<int> randomize(int size, int modulo = 10000)
{
	std::vector<int> result;
	for (int i = 0; i < size; i++) 
	{ 
		result.push_back(rand() % modulo);
	}
	return result;
}

//template <typename T>
//void merge(std::vector<T>& arr, int left, int middle, int right)
//{
//	std::vector<T> buffer;
//	int i = left, j = middle + 1;
//
//	while (i <= middle && j <= right)
//	{
//		if (arr[i] <= arr[j]) 
//		{
//			buffer.push_back(arr[i]);
//			i++;
//		}
//		else
//		{
//			buffer.push_back(arr[j]);
//			j++;
//		}
//	}
//
//	while (i <= middle)
//	{
//		buffer.push_back(arr[i]);
//		i++;
//	}
//
//	while (j <= right)
//	{
//		buffer.push_back(arr[j]);
//		j++;
//	}
//
//	for (int k = left; k <= right; k++)
//		arr[k] = buffer[k - left];
//}

template <typename main_iter, typename auxil_iter>
void merge(main_iter left, main_iter middle, main_iter right, auxil_iter aux_left)
{
	main_iter beg = left, end = middle;
	auxil_iter temp_left = aux_left;

	while (beg != middle && end != right)
	{
		if (*beg <= *end)
		{
			*temp_left = std::move(*beg);
			++temp_left;
			++beg;
		}
		else
		{
			*temp_left = std::move(*end);
			++temp_left;
			++end;
		}
	}

	while (beg != middle)
	{
		*temp_left = std::move(*beg);
		++temp_left;
		++beg;
	}

	while (end != right)
	{
		*temp_left = std::move(*end);
		++temp_left;
		++end;
	}
	
	std::move(aux_left, temp_left, left);
}

template <typename main_iter, typename auxil_iter>
void mergesort_do(main_iter left, main_iter right, auxil_iter aux_left)
{
	const auto size = std::distance(left, right);

	if (size < 2) {
		return;
	}

	auto middle = std::next(left, size / 2);
	mergesort_do(left, middle, aux_left);
	mergesort_do(middle, right, std::next(aux_left, std::distance(left, middle)));
	merge(left, middle, right, aux_left);
}

template <typename main_iter>
void mergesort(main_iter left, main_iter right)
{
	const int size = std::distance(left, right);
	std::vector<main_iter::value_type> buffer(size);
	mergesort_do(left, right, buffer.data());
}

//template <typename T>
//void mergesort_multithread(std::vector<T>& arr, int left, int right)
//{
//	if (left < right)
//	{
//		int middle = left + (right - left) / 2;
//		std::thread t1(mergesort_multithread<T>, std::ref(arr), left, middle);
//		std::thread t2(mergesort_multithread<T>, std::ref(arr), middle + 1, right);
//		t1.join();
//		t2.join();
//		merge(arr, left, middle, right);
//	}
//}



