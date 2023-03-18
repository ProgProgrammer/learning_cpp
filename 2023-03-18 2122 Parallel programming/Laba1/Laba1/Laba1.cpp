#include <iostream>
#include <omp.h>
#include <time.h>
#include <vector>

int count;
int its_me;

void first_task()  // Написать многопоточную программу, используя директивы OpenMP
{
    std::cout << "10 threads:" << std::endl;
#pragma omp parallel num_threads(10)
    {
        count = omp_get_num_threads();
        its_me = omp_get_thread_num();
        printf("Hello, OpenMP! I am %d of %d\n", its_me, count);
    }
    std::cout << std::endl << "1 thread:" << std::endl;
#pragma omp parallel num_threads(1)
    {
        count = omp_get_num_threads();
        its_me = omp_get_thread_num();
        printf("Hello, OpenMP! I am %d of %d\n", its_me, count);
    }
    std::cout << std::endl << "5 threads:" << std::endl;
#pragma omp parallel num_threads(5)
    {
        count = omp_get_num_threads();
        its_me = omp_get_thread_num();
        printf("Hello, OpenMP! I am %d of %d\n", its_me, count);
    }
    std::cout << std::endl << "10 threads:" << std::endl;
#pragma omp parallel num_threads(10)
    {
        count = omp_get_num_threads();
        its_me = omp_get_thread_num();
        printf("Hello, OpenMP! I am %d of %d\n", its_me, count);
    }
}

double elapsedTime(clock_t start, clock_t end)
{
    return (double)(end - start) / CLOCKS_PER_SEC;
}

void second_task()
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
        for (int i = 0; i < count; ++i)
        {
#pragma omp atomic
            result += arr[i];
        }
    }
    end = clock();
    std::cout << "Result = " << result << std::endl;
    std::cout << "Atomic option = " << elapsedTime(start, end) << std::endl << std::endl;
}

int main()
{
    //first_task();
    second_task();
}