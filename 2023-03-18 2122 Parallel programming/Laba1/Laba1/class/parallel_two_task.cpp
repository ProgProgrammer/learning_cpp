#include "parallel.h"
#include <iostream>
#include <vector>
#include <omp.h>

void Parallel::two_task()
{
    const int count = 100000000;
    std::vector<int> arr;

    for (int i = 0; i < count; ++i)
    {
        arr.push_back(i);
    }

    clock_t start;
    clock_t end;

    int result = 0;
    start = clock();
    for (int i = 0; i < count; ++i)
    {
        result += arr[i];
    }
    end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Sequential option = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    start = clock();
#pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < count; ++i)
    {
        result += arr[i];
    }
    end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Reduction option = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    int result_part_one = 0;
    int result_part_two = 0;
    start = clock();
#pragma omp parallel sections num_threads(2)
    {
#pragma omp section
        {
            for (int i = 0; i < 50000000; ++i)
            {
                result_part_one += arr[i];
            }
        }

#pragma omp section
        {
            for (int i = 50000000; i < count; ++i)
            {
                result_part_two += arr[i];
            }
        }
    }
    end = clock();
    std::cout << "Result = " << result_part_one + result_part_two << std::endl;
    std::cout << "Sections option = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    int i;
    start = clock();
#pragma omp parallel shared (result, arr) private (i)
    {
#pragma omp for
        for (i = 0; i < count; ++i)
        {
#pragma omp atomic
            result += arr[i];
        }
    }
    end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Atomic option = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    start = clock();
#pragma omp parallel for num_threads(4)
        for (int i = 0; i < count; ++i)
        {
#pragma omp critical
            {
                result += arr[i];
            }
        }
    end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Critical option = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    start = clock();
#pragma omp parallel for num_threads(4)
        for (int i = 0; i < count; ++i)
        {
#pragma omp critical
            {
                result += arr[i];
            }
        }
    end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Doubling algorithm option = " << elapsedTime(start, end) << std::endl << std::endl;
}