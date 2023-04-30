#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "merge_sort.h"
#include "merge_sort_multithread.h"
#include "utils.h"

#include "doctest.h"


TEST_CASE("Validity test: Merge sort is equal to std::sort") {
	srand(time(0));
	std::cout << "\nValidity test: Merge sort is equal to std::sort.\n";
	for (int i = 2; i <= 10 * 100; i *= 100)
	{
		for (int s = 0; s < 5; s++)
		{
			std::vector<int> test = randomize(i, 2 * i);
			auto test2 = test, test3 = test;

			Merge::mergesort(test.begin(), test.end());
			MultiMerge::mergesort(test2.begin(), test2.end());
			std::sort(test3.begin(), test3.end());
			CHECK(test == test2);
			CHECK(test == test3);
		}
	}
}


TEST_CASE("\nSpeedtesting: merge sort, multithreaded merge sort, std::sort") {
	srand(time(0));
	int start_size = 50;
	int	end_size = 50000000;
	int number_of_threads = 8;

	std::cout << "\n\nSpeedtesting merge sort, multithreaded merge sort, std::sort.\n";

	for (int i = start_size; i <= end_size; i *= 10)
	{
			std::vector<int> test = randomize(i, 2 * i);
			auto test2 = test, test3 = test;
			
			auto mrg_sort_dur = time_evaluation(Merge::mergesort<std::vector<int>::iterator>,
				test.begin(), test.end());
			auto mrg_sort_multithread_dur = time_evaluation(MultiMerge::mergesort<std::vector<int>::iterator>,
				test2.begin(), test2.end(), number_of_threads);
			auto std_sort_dur = time_evaluation(std::sort<std::vector<int>::iterator>, 
				test3.begin(), test3.end());

			double speedup_coef = double(mrg_sort_dur) / mrg_sort_multithread_dur;

			CHECK(test == test3);
			CHECK(test2 == test3);

			int width = 28;

			std::cout << std::setw(5) << i << std::setw(width) << "Merge sort" 
				<< std::setw(width) << "Merge multithread sort"
				<< std::setw(width) << "std::sort"
				<< std::setw(width) << "Speedup Coefficient\n";

			std::cout << std::setw(width) << mrg_sort_dur << "ms" 
				<< std::setw(width) << mrg_sort_multithread_dur << "ms"
				<< std::setw(width) << std_sort_dur << "ms"
				<< std::setw(width) << speedup_coef << " times" << "\n\n";
	}
}


TEST_CASE("\Speedtesting different amount of threads") {
	srand(time(0));
	int start_size = 500;
	int	end_size = 50000000;
	int max_number_of_threads = 16;

	std::cout << "\n\nSpeedtesting multithreaded merge sort for different amount of threads.\n";

	for (int i = start_size; i <= end_size; i *= 10)
	{
		std::vector<int> test = randomize(i, 2 * i);
		std::cout << "SIZE " << i << ":\n";

			for (int x = 1; x <= max_number_of_threads; x *= 2)
			{
				auto temp_test = test;
				std::cout << x << " threads - " << time_evaluation(MultiMerge::mergesort<std::vector<int>::iterator>,
					temp_test.begin(), temp_test.end(), x) << "ms\n";
			}

		std::cout << "\n\n";
	}
}

/*TEST_CASE("\nOLD Speedtesting: merge sort, multithreaded merge sort, std::sort") {
	//srand(time(0));
	int start_size = 50;
	int	end_size = 50000000;
	std::clock_t start, end;

	std::cout << "\n\nOLD Speedtesting merge sort, multithreaded merge sort, std::sort.\n\n";

	for (int i = start_size; i <= end_size; i *= 10)
	{
		std::vector<int> test = randomize(i, 2 * i);
		auto test2 = test, test3 = test;

		start = clock();
		mergesort(test.begin(), test.end());
		end = clock();
		auto mrg_sort_dur = end-start;

		start = clock();
		mergesort_multithread(test2.begin(), test2.end());
		end = clock();
		auto mrg_sort_multithread_dur = end - start;

		start = clock();
		std::sort(test3.begin(), test3.end());
		end = clock();
		auto std_sort_dur = end - start;

		CHECK(test == test3);
		CHECK(test2 == test3);

		int width = 28;

		std::cout << std::setw(5) << i << std::setw(width) << "Merge sort"
			<< std::setw(width) << "Merge multithread sort"
			<< std::setw(width) << "std::sort\n";

		std::cout << std::setw(width) << mrg_sort_dur << "ms"
			<< std::setw(width) << mrg_sort_multithread_dur << "ms"
			<< std::setw(width) << std_sort_dur << "ms" << "\n\n";
	}
}*/