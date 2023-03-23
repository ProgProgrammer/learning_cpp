#include "parallel.h"
#include <vector>
#include <omp.h>

void Parallel::four_task()
{
    const int min_count = 10000;
    const int max_count = 1000000;
    std::vector<int> min_arr;
    std::vector<int> max_arr;

    for (int i = 0; i < max_count; ++i)
    {
        if (i < min_count)
        {
            min_arr.push_back(i);
        }

        max_arr.push_back(i);
    }

    clock_t start;
    clock_t end;

    int result = 0;
    start = clock();
#pragma omp parallel for schedule(static)
    for (int i = 0; i < min_count; ++i)
    {
        result += min_arr[i];
    }
    std::cout << "Static minimum result = " << result << std::endl;

    result = 0;
#pragma omp parallel for schedule(static)
    for (int i = 0; i < max_count; ++i)
    {
        result += max_arr[i];
    }
    end = clock();
    std::cout << "Static maximum result = " << result << std::endl;
    std::cout << "Time = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    start = clock();
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < min_count; ++i)
    {
        result += min_arr[i];
    }
    std::cout << "Dynamic minimum result = " << result << std::endl;

    result = 0;
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < max_count; ++i)
    {
        result += max_arr[i];
    }
    end = clock();
    std::cout << "Dynamic maximum result = " << result << std::endl;
    std::cout << "Time = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    start = clock();
#pragma omp parallel for schedule(guided)
    for (int i = 0; i < min_count; ++i)
    {
        result += min_arr[i];
    }
    std::cout << "Guided minimum result = " << result << std::endl;

    result = 0;
#pragma omp parallel for schedule(guided)
    for (int i = 0; i < max_count; ++i)
    {
        result += max_arr[i];
    }
    end = clock();
    std::cout << "Guided maximum result = " << result << std::endl;
    std::cout << "Time = " << elapsedTime(start, end) << std::endl << std::endl;
}