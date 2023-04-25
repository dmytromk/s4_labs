#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "quick_sort.h"

#include "doctest.h"
#include <time.h>

TEST_CASE("Validity test: Merge sort is equal to std::sort") {
	std::cout << "\nValidity test: Merge sort is equal to std::sort: ";
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
	int start_size = 10;
	int	end_size = 1000000;
	std::clock_t start, end;
	std::cout << "\n\nSpeedtesting merge sort, multithreaded merge sort, std::sort\n\n";
	for (int i = start_size; i <= end_size; i *= 10)
	{
			std::vector<int> test = randomize(i, 2 * i);
			auto test2 = test, test3 = test;

			start = clock();
			mergesort(test.begin(), test.end());
			end = clock();
			double mrg_sort_dur = end - start;

			/*start = clock();
			mergesort_multithread(test2, 0, test2.size() - 1);
			end = clock();
			auto mrg_sort_multithread_dur = end - start;*/

			start = clock();
			std::sort(test3.begin(), test3.end());
			end = clock();
			double std_sort_dur = end - start;

			CHECK(test == test3);

			int width = 25;

			std::cout << std::setw(8) << i << std::setw(width) << "Merge sort" << std::setw(width) << "std::sort\n";
			std::cout << std::setw(width) << mrg_sort_dur << "ms" << std::setw(width) << std_sort_dur << "ms" << "\n\n";
	}
}

//TEST_CASE("speedtesting for the strassen algorithm") {
//	srand(time(0));
//	int start_size = 100;
//	int	end_size = 800;
//	std::clock_t start, end;
//	std::cout << "Speedtesting the Strassen algorithm";
//	for (int i = start_size; i <= end_size; i *= 2) {
//		ComplexMatrix m1(i, i);
//		ComplexMatrix m2(i, i);
//		m1.auto_gen(1, 5, 1, 5);
//		m2.auto_gen(1, 5, 1, 5);
//		start = clock();
//		ComplexMatrix lol = m1*m2;
//		end = clock();
//		std::cout << "\nRegular multiplication:";
//		std::cout << "\nN = " << i;
//		std::cout << "\nDuration: " << end - start << " ms";
//		start = clock();
//
//		ComplexMatrix* res = Strassen(&m1, &m2);
//		end = clock();
//		std::cout << "\nStrassen multiplication:";
//		std::cout << "\nN = " << i;
//		std::cout << "\nDuration: " << end - start << " ms";
//		bool checker = (*res == (m1 * m2));
//		delete res;
//		CHECK(checker);
//		std::cout << "\n\n";
//	}
//	std::cout << "\n";
//}