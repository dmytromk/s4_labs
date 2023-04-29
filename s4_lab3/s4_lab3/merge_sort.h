#pragma once
#include <vector>
#include <algorithm>

template <typename main_iter, typename auxil_iter>
void merge(const main_iter left, const main_iter middle, const main_iter right, const auxil_iter aux_left)
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
void mergesort_do(const main_iter left, const main_iter right, const auxil_iter aux_left)
{
	const auto size = std::distance(left, right);

	if (size < 2) {
		return;
	}

	const auto middle = std::next(left, size / 2);
	mergesort_do(left, middle, aux_left);
	mergesort_do(middle, right, std::next(aux_left, std::distance(left, middle)));
	merge(left, middle, right, aux_left);
}

template <typename main_iter>
void mergesort(const main_iter left, const main_iter right)
{
	std::vector<typename main_iter::value_type> buffer(std::distance(left, right));
	mergesort_do(left, right, buffer.begin());
}



