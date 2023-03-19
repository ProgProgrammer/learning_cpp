#include "parallel.h"
#include <iostream>
#include <omp.h>

void Parallel::one_task()
{
    int count;
    int its_me;

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