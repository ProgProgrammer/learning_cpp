#include "parallel.h"
#include <vector>
#include <omp.h>

void Parallel::five_task()
{
    const int count = 1000000000;
    std::vector<int> arr;

    for (int i = 0; i < count; ++i)
    {
        arr.push_back(i);
    }

    int result = 0;
    int num = 0;
    int max_count = 0;
    int threads_count = 2;
    clock_t start = clock();
#pragma omp parallel sections num_threads(threads_count)
    {
#pragma omp section
        {
            for (int i = 0; i < 500000000; ++i)
            {
                if (arr[i] > result)
                {
                    result = arr[i];
                }
            }
        }
#pragma omp section
        {
            for (int i = 500000000; i < count; ++i)
            {
                if (arr[i] > result)
                {
                    result = arr[i];
                }
            }
        }
    }
    clock_t end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Time doubling algorithm option = " << elapsedTime(start, end) << std::endl << std::endl;
}