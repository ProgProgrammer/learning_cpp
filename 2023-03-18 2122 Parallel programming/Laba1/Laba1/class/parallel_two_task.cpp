#include "parallel.h"
#include <vector>
#include <omp.h>

void Parallel::two_task()
{
    const int count = 100000000;
    std::vector<float> arr;
    float num = 1.15;

    for (int i = 0; i < count; ++i)
    {
        ++num;
        arr.push_back(num);
    }

    clock_t start;
    clock_t end;

    float result = 0;
    start = clock();
    for (int i = 0; i < count; ++i)
    {
        result += arr[i];
    }
    end = clock();
    std::ios_base::fmtflags orig = std::cout.setf(std::ios_base::fixed,
        std::ios_base::floatfield);
    std::streamsize prec = std::cout.precision(20);
    std::cout << "Result = " << result << std::endl;
    std::cout << "Time sequential option = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    start = clock();
#pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < count; ++i)
    {
        result += arr[i];
    }
    end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Time reduction option = " << elapsedTime(start, end) << std::endl << std::endl;

    float result_part_one = 0;
    float result_part_two = 0;
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
    std::cout << "Time sections option = " << elapsedTime(start, end) << std::endl << std::endl;

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
    std::cout << "Time atomic option = " << elapsedTime(start, end) << std::endl << std::endl;

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
    std::cout << "Time critical option = " << elapsedTime(start, end) << std::endl << std::endl;

    result = 0;
    start = clock();
#pragma omp parallel for reduction(+:result)	
    for (int i = 0; i < count; i++)
        result += arr[i];
    end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Time doubling algorithm option = " << elapsedTime(start, end) << std::endl << std::endl;
}