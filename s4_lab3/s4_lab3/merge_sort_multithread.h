#pragma once
#include "merge_sort.h"

#include <thread>

namespace MultiMerge {
	template <typename main_iter, typename auxil_iter>
	void mergesort_do(const main_iter left, const main_iter right, const auxil_iter aux_left, int cur_thread_amount, int max_threads)
	{
		const auto size = std::distance(left, right);

		if (size < 2) {
			return;
		}

		const auto middle = std::next(left, size / 2);
		const auto aux_middle = std::next(aux_left, std::distance(left, middle));

		if (cur_thread_amount < max_threads)
		{
			cur_thread_amount += 2;

			std::thread th1(&mergesort_do<main_iter, auxil_iter>,
				left, middle, aux_left, cur_thread_amount, max_threads);

			std::thread th2(&mergesort_do<main_iter, auxil_iter>,
				middle, right, aux_middle, cur_thread_amount, max_threads);

			th1.join();
			th2.join();
		}

		else
		{
			mergesort_do(left, middle, aux_left, cur_thread_amount, max_threads);
			mergesort_do(middle, right, std::next(aux_left, std::distance(left, middle)), cur_thread_amount, max_threads);
		}

		Merge::merge(left, middle, right, aux_left);
	}


	template <typename main_iter>
	void mergesort(const main_iter left, const main_iter right, int max_threads = 8) //max amount of threads MUST BE POW OF 2
	{
		std::vector<typename main_iter::value_type> buffer(std::distance(left, right));
		mergesort_do(left, right, buffer.begin(), 0, max_threads);
	}
}