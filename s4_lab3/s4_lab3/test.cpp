#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "merge_sort.h"
#include "utils.h"

#include "doctest.h"
#include <time.h>

TEST_CASE("Validity test: Merge sort is equal to std::sort") {
	std::cout << "\nValidity test: Merge sort is equal to std::sort.\n";
	for (int i = 2; i <= 10 * 100; i *= 100)
	{
		for (int s = 0; s < 5; s++)
		{
			std::vector<int> test = randomize(i, 2 * i);
			auto test2 = test, test3 = test;

			mergesort(test.begin(), test.end());
			//mergesort_multithread(test2, 0, test.size() - 1);
			std::sort(test3.begin(), test3.end());
			//CHECK(test == test2);
			CHECK(test == test3);
			std::cout << "\nSuccess";
		}
	}
}

TEST_CASE("\nSpeedtesting: merge sort, multithreaded merge sort, std::sort") {
	srand(time(0));
	int start_size = 50;
	int	end_size = 50000000;
	std::clock_t start, end;

	std::cout << "\n\nSpeedtesting merge sort, multithreaded merge sort, std::sort.\n\n";

	for (int i = start_size; i <= end_size; i *= 10)
	{
			std::vector<int> test = randomize(i, 2 * i);
			auto test2 = test, test3 = test;
			
			/*start = clock();
			mergesort(test.begin(), test.end());
			end = clock();*/
			auto mrg_sort_dur = time_evaluation(mergesort<std::vector<int>::iterator>, test.begin(), test.end());

			/*start = clock();
			mergesort_multithread(test2, 0, test2.size() - 1);
			end = clock();
			auto mrg_sort_multithread_dur = end - start;*/

			/*start = clock();
			std::sort(test3.begin(), test3.end());
			end = clock();*/
			auto std_sort_dur = time_evaluation(mergesort<std::vector<int>::iterator>, test3.begin(), test3.end());

			CHECK(test == test3);

			int width = 25;

			std::cout << std::setw(10) << i << std::setw(width) << "Merge sort" << std::setw(width) << "std::sort\n";
			std::cout << std::setw(width) << mrg_sort_dur << "ms" << std::setw(width) << std_sort_dur << "ms" << "\n\n";
	}
}